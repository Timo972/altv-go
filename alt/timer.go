package alt

import "time"

type timerListener = func()

var timerClears = make(map[uint64]chan bool)

func createTimer(listener timerListener, ms uint64, once bool) uint64 {
	interval := time.Duration(ms) * time.Millisecond

	ticker := time.NewTimer(interval)
	clear := make(chan bool)

	id := uint64(len(timerClears))
	timerClears[id] = clear

	go func() {
		for {
			select {
				case <-ticker.C:
					go listener()
					if once {
						ticker.Stop()
						delete(timerClears, id)
						return
					}
					case <-clear:
						ticker.Stop()
						delete(timerClears, id)
						return
			}
		}
	}()

	return id
}

func ClearTimer(id uint64) bool {
	clear := timerClears[id]

	if clear == nil {
		return false
	}

	delete(timerClears, id)
	return true
}

func SetInterval(listener timerListener, ms uint64) uint64 {
	return createTimer(listener, ms, false)
}

func SetTimeout(listener timerListener, ms uint64) uint64 {
	return createTimer(listener, ms, true)
}

func EveryTick(listener timerListener) uint64 {
	return createTimer(listener, 0, false)
}

func NextTick(listener timerListener) uint64 {
	return createTimer(listener, 1, true)
}