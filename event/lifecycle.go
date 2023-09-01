package event

import "C"
import "slices"

type lifecycleListener func()

func (s *subscriber) Start(lis lifecycleListener) int {
	s.startEvents = append(s.startEvents, lis)
	return len(s.startEvents) - 1
}

func (s *subscriber) Stop(lis lifecycleListener) int {
	s.stopEvents = append(s.stopEvents, lis)
	return len(s.stopEvents) - 1
}

func (s *unsubscriber) Start(id int) error {
	if id < 0 || id >= len(s.sub.startEvents) {
		return ErrInvalidEventID
	}

	s.sub.startEvents = slices.Delete(s.sub.startEvents, id, 1)
	return nil
}

func (s *unsubscriber) Stop(id int) error {
	if id < 0 || id >= len(s.sub.stopEvents) {
		return ErrInvalidEventID
	}

	s.sub.stopEvents = slices.Delete(s.sub.stopEvents, id, 1)
	return nil
}

//export OnStart
func OnStart() {
	processEventQueue()
	for _, event := range once.startEvents {
		event()
	}
	clear(once.startEvents)

	for _, event := range on.startEvents {
		event()
	}
}

//export OnStop
func OnStop() {
	for _, event := range once.stopEvents {
		event()
	}
	clear(once.stopEvents)

	for _, event := range on.stopEvents {
		event()
	}
}
