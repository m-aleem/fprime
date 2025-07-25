# Svc::EventManager Component

## 1. Introduction

The `Svc::EventManager` component processes events from other components. The events are put in packets and sent to an
external component like the ground interface. The component provides event filtering capability such that events may
be turned off via ID or severity.

## 2. Requirements

The requirements for `Svc::EventManager` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
AL-001 | The `Svc::EventManager` component shall receive events and compose them into downlink packets. | Inspection; Unit Test
AL-002 | The `Svc::EventManager` component shall have commands to filter events based on event severity. | Unit Test
AL-003 | The `Svc::EventManager` component shall have commands to filter events based on the event ID. | Unit Test 
AL-004 | The `Svc::EventManager` component shall call fatalOut port when FATAL is received | Inspection; Unit Test

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Svc::EventManager` component has the following component diagram:

![`Svc::EventManager` Diagram](img/EventManagerBDD.jpg "Svc::EventManager")

#### 3.1.2 Ports

The `Svc::EventManager` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----
[`Fw::Log`](../../../Fw/Log/docs/sdd.md) | LogRecv | Input | Synchronous | Receive events from components
[`Fw::Com`](../../../Fw/Log/docs/sdd.md) | PktSend | Output | n/a | Send event packets to external user
[`Svc::FatalEvent`](../../../Svc/Fatal/docs/sdd.md) | FatalAnnounce | Output | n/a | Send FATAL event (to health)

### 3.2 Functional Description

The `Svc::EventManager` component provides an event logging function for the software. The framework autocoder allows
developers to specify a set of events in the component FPP.
(see [Events](../../../docs/user-manual/overview/04-cmd-evt-chn-prm.md). For these components, the
autocoder will add an `Fw::Log` output port to send events in serialized form. The EventManager receives these port
calls and provides commands to filter these events. The filtered events are sent to other components such as the ground
interface. 
 
**Note:** the Event ID value 0 is reserved for the logger.

Should a FATAL severity event arrive, it is announced using a FATAL out port allow the system to respond when a FATAL
event is seen.

#### 3.2.1 Filtering

The `Svc::EventManager` `LogRecv` input port handler filters events to lessen the load on the downstream components. The
filters can be set by severity and ID. By default, the DIAGNOSTIC events are filtered out since the number of DIAGNOSTIC
events can be quite high.  All defaults can be globally configured in `config/EventManagerCfg.hpp`. Filters are
modified at runtime by the `SET_EVENT_FILTER` command.

The component also allows filtering events by event ID. There is a configuration parameter that sets the number of IDs
that can be filtered. This allows operators to mute a particular event that might be flooding the downstream components.
These filters are modified at runtime by the `SET_ID_FILTER` command.

FATAL events are never filtered, so they can be caught and broadcast to the system. Outgoing events are converted into
the F´ ground format and sent out using the `PktSend` port.



#### 3.2.2 Fatal Announce

When the `EventManager` component receives a FATAL event, it calls the FatalAnnounce port. Another component that
handles the system response to FATALs (such as resetting the system) can connect to this port to be informed when a
FATAL has occurred.

### 3.3 Scenarios

#### 3.3.1 Receive Events

The `Svc::EventManager` component accepts events from other components.

### 3.4 State

`Svc::EventManager` has no state machines, but stores the state of the event severity and event ID filters.

### 3.5 Algorithms

`Svc::EventManager` has no significant algorithms.

## 4. Dictionaries

TBD

## 5. Unit Testing

To see unit test coverage run fprime-util check --coverage

## 6. Change Log

Date | Description
---- | -----------
6/25/2015 | Design review edits
7/22/2015 | Design review actions
9/7/2015 | Unit Test updates 
10/28/2015 | Added FATAL announce port
12/1/2020 | Removed event buffers and post-filter



