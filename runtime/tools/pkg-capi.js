const fs = require("fs");
const path = require("path");
const { promisify } = require("util");

const readFile = promisify(fs.readFile);
const readDir = promisify(fs.readdir);
const writeFile = promisify(fs.writeFile);

const definitionRegex =
  /*/^[\/]{0,0}EXPORT\s([a-zA-Z0-9\s\*]{1,}[\s\*]{1,1})([A-Z]{1,1}[a-zA-Z]+)_([a-zA-Z0-9]+)\(([a-zA-Z0-9\s\*\,]{0,})\);/gm*/ /EXPORT\s([a-zA-Z0-9\s\*]{1,}[\s\*]{1,1})([A-Z]{1,1}[a-zA-Z]+)_([a-zA-Z0-9]+)\(([a-zA-Z0-9\s\*\,]{0,})\);/gm;
// match: whole line
// group 1: return type
// group 2: class name
// group 3: cpp-sdk func name
// group 4: arg as string, seperated by comma

const typedefRegex =
  /typedef\s[a-z]+\s[a-zA-Z0-9\s]+{[^}]+}[\s]{0,1}[a-zA-Z0-9]+;/gm;
// match whole struct typedef

function camelCaseToSnakeCase(str) {
  for (var i = 0; i < str.length; i++) {
    const char = str.charAt(i);

    const isUpper = /[A-Z]/g.test(char);

    if (i === 0 && isUpper)
      str = char.toLocaleLowerCase() + str.substring(1, str.length);
    else if (isUpper)
      str =
        str.substring(0, i) +
        "_" +
        char.toLocaleLowerCase() +
        str.substring(i + 1, str.length);
  }

  return str;
}

function generateCTypedef(returnValue, className, methodName, args) {
  const fn = `capi_${camelCaseToSnakeCase(className + methodName)}`;
  const typedef = `typedef ${returnValue} (*${fn})(${args});\n`;

  return [typedef, fn];
}

function generateCFuncDef(returnValue, className, methodName, args) {
  const func = `${returnValue} ${camelCaseToSnakeCase(
    className + methodName
  )}(${args});\n`;

  return func;
}

function generateCFuncInit(typedefName, pureName) {
  const callName = `g_call_${pureName}`;
  return [`${typedefName} ${callName};\n`, callName];
}

function generateCGetFunc(cFuncInitName, className, methodName, typedefName) {
  return `${cFuncInitName} = GET_FUNC(module, "${className}_${methodName}", ${typedefName});\n`;
}

function generateCFuncBody(returnType, pureName, argStr) {
  const args = argStr.split(",").map((val) => {
    const lastIdxOfSpace = val.lastIndexOf(" ") + 1;
    let type = val.substring(0, lastIdxOfSpace).trim();
    let name = val.substring(lastIdxOfSpace, val.length);
    if (name.charAt(0) === "*") {
      name = name.substring(1, name.length);
      type += " *";
    }
    return name;
  });

  if (returnType === "void")
    return `
${returnType} ${pureName}(${argStr})
{
    g_call_${pureName}(${args.join(", ")});
}\n`;
  else
    return `
${returnType} ${pureName}(${argStr})
{
    return g_call_${pureName}(${args.join(", ")});
}\n`;
}

function loadModuleStuff(lines) {
  return `
int load_module(const char *path)
{
    module = LOAD_LIB(path);

    if (module == NULL)
    {
        return 0;
    }

    ${lines.join("\n")}

    return 1;
}
`;
}

function generateCApiPartial(definitionPath, definitionContent) {
  return new Promise((resolve, reject) => {
    let hContent = `// ${definitionPath} Module.h\n`;
    let hFuncDefs = `// ${definitionPath} Module.h\n`;
    let cContent = `// ${definitionPath} Module.c\n`;
    let cLoadModuleFunc = `// ${definitionPath} int load_module(const char *path);\n`;
    let cFuncBodys = `// ${definitionPath}  Module.c\n`;
    let match;

    while ((match = definitionRegex.exec(definitionContent)) != null) {
      if (match.index === definitionRegex.lastIndex) {
        definitionRegex.lastIndex++;
      }

      const returnType = match[1].trim();

      const [typedef, name] = generateCTypedef(
        returnType,
        match[2],
        match[3],
        match[4]
      );
      const func = generateCFuncDef(returnType, match[2], match[3], match[4]);

      const snakeName = name.substring(5, name.length);

      const [cInit, callName] = generateCFuncInit(name, snakeName);
      const cFunc = generateCGetFunc(callName, match[2], match[3], name);
      const cFuncBody = generateCFuncBody(returnType, snakeName, match[4]);

      if (
        typeof typedef !== "string" ||
        typeof func !== "string" ||
        typeof cInit !== "string" ||
        typeof cFunc !== "string" ||
        typeof cFuncBody !== "string" ||
        typeof callName !== "string"
      ) {
        reject(`invalid return of generateCTypedef, check script!`);
        return;
      } else hContent += typedef;
      cContent += cInit;
      hFuncDefs += func;
      cLoadModuleFunc += cFunc;
      cFuncBodys += cFuncBody;
    }

    cContent += "\n\n";
    hContent += "\n\n";
    hContent += hFuncDefs;
    cContent += "\n\n";
    cContent += cFuncBodys;

    resolve([hContent, cContent, cLoadModuleFunc]);
  });
}

const files = [
  // we need the structs
  path.join(__dirname, "../src/Main.h"),
  // c-api definitions
  path.join(__dirname, "../src/capi/")
];

const cBegin = `
#include "capi.h"

Module module;
`;

const hBegin = `
#ifndef CAPI_MODULE
#define CAPI_MODULE

#ifndef __linux__
#include <Windows.h>

#define SEPARATOR "\\\\"
#define LOAD_LIB(path) LoadLibrary(path)
#define GET_FUNC(module, name, type) (type) GetProcAddress(module, name);

typedef HINSTANCE Module;
#else
#include <stddef.h>
#include <dlfcn.h>

#define SEPARATOR "/"
#define LOAD_LIB(name) dlopen(name, RTLD_NOW);
#define GET_FUNC(module, name, type) (type) dlsym(module, name);

typedef void *Module;
#endif

int load_module(const char *path);
`;

async function main() {
  // check for necessary files
  files.forEach((p) => {
    if (!fs.existsSync(p)) {
      throw new Error(
        `Could not find file: '${p}' tool must be run in project root`
      );
    }
  });

  // filter c-api definitions
  const res = (await readDir(files[1]))
    .filter((f) => f.endsWith(".h"))
    .map((f) => path.join(files[1], f));
  if (res.length < 1)
    throw new Error(`Could not find any c-api definitions ('${files[1]}')`);

  console.log(`reading ${res.length} file(s)...`);

  // read c-api definitions
  const partials = await Promise.all(
    res.map(async (fp) => {
      const definitionContent = await readFile(fp, {
        encoding: "utf8",
      });

      return await generateCApiPartial(fp, definitionContent);
    })
  );

  console.log(`joining partials...`);

  // join c-api partials (header & source)
  let h = partials.map((x) => x[0]).join("\n");
  const c = partials.map((x) => x[1]).join("\n");
  const d = partials.map((x) => x[2]);

  const getFuncsStr = loadModuleStuff(d);

  console.log(`including ${files[0]} typedefs...`);
  const mainH = await readFile(files[0], {
    encoding: "utf8",
  });

  let typedefs = "";
  let m;
  while ((m = typedefRegex.exec(mainH)) !== null) {
    if (m.index === typedefRegex.lastIndex) {
      typedefRegex.lastIndex++;
    }

    m.forEach((match) => {
      typedefs += "\n" + match + "\n";
    });
  }

  console.log("writing package c-api...");

  if (!fs.existsSync("./out")) fs.mkdirSync("./out");
  await writeFile(
    `./out/capi.h`,
    hBegin + "\n" + typedefs + "\n" + h + "\n" + "\n#endif"
  );
  await writeFile(`./out/capi.c`, cBegin + "\n" + c + "\n\n" + getFuncsStr);

  console.log("done!");
}

main();
