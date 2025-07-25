# Configuring F´

This guide is a first attempt to describe the various configuration settings in F´.  Most users can operate with the
default settings, but as the system design is finalized, some of these options may need to be changed such that the
system is most efficient.

This guide includes:

- [How to Configure F´](#how-to-configure-f)
- [AcConstants.fpp](#acconstantsfpp)
- [FpConfig.hpp](#fpconfigh)
    - [Type Settings](#type-settings)
    - [Object Settings](#object-settings)
    - [Asserts](#asserts)
    - [Port Tracing](#port-tracing)
    - [Port Serialization](#port-serialization)
    - [Serialization Type ID](#serializable-type-id)
    - [Buffer Sizes](#buffer-sizes)
    - [Text Logging](#text-logging)
    - [Misc Configuration Settings](#misc-configuration-settings)
- [Component Configuration](#component-configuration)
- [Conclusion](#conclusion)


## How To Configure F´

All configurable files (top-level and component-specific) for F´ are available in the top-level
`config` directory. By default, all deployments use the F´ provided default configuration options.

Projects can also take ownership of the `config` directory to provide their own `AcConstants.fpp`
and configuration `*.hpp` files. To do so, copy the `config` directory into your project and use the
`config_directory` options in the project's `settings.ini` file.
See the [settings.ini guide](../build-system/settings.md) for more details.

The `FpConfig.h` file is a C header allowing the user to define global settings.
Where components allow specific configuration, a `<component>Cfg.hpp` is available to be modified as well.

## AcConstants.fpp

`AcConstants.fpp` is used to set the constants for the autocoded components provided by the framework. This allows
projects to appropriately size the number of ports provided by many of the command and data handling components defined
in the `Svc` package.

> [!NOTE]
> Internal configurations like table sizes are set in the component-specific header as these settings aren't autocoded. See: [Component Configuration](#component-configuration)

These settings may need to be increased for large projects with many components, or minimized for projects with a small
number of components.

| Setting                            | Description                                                                                           | Default | Valid Values     |
|------------------------------------|-------------------------------------------------------------------------------------------------------|---------|------------------|
| ActiveRateGroupOutputPorts         | Number of outputs from active rate group. Limits number of components attached to a single rate group | 10      | Positive integer |
| CmdDispatcherComponentCommandPorts | Number of command and command registration ports. Limits number of components handling commands       | 30      | Positive integer |
| CmdDispatcherSequencePorts         | Number of incoming ports to command dispatcher, e.g. uplink and command sequencer                     | 5       | Positive integer |
| RateGroupDriverRateGroupPorts      | Number of rate group driver output ports. Limits total number of different rate groups                | 3       | Positive integer |
| HealthPingPorts                    | Number of health ping output ports. Limits number of components attached to health component          | 25      | Positive integer |
| SeqDispatcherSequencerPorts         | Number of CmdSequencers that the SeqDispatcher can dispatch sequences to | 2 | Positive integer

## FpConfig.h

Some configurations may be changed during compilation time. The F′ framework has a number of optional features that can
be enabled or disabled by editing the `config/FpConfig.h` file.  These changes affect of the whole of the F´
deployment. Users can change or override defined *C* macro values that activate or disable code by using compiler flags
for different deployment settings. During flight software (FSW) execution, disabling unnecessary features saves memory
and CPU cycles.

All of these settings should be set in `FpConfig.h` and for most projects, this whole file will be cloned and owned
for their specific settings. Typically, the user will define the setting to be 0 for off and 1 for on.

e.g.
```c
#define FW_SOME_SETTING 1
```

### Type Settings

Many architectures support different sizes of types. In addition, projects may wish to change the size of the various
custom types specified in the framework. This section will describe these settings. These are typically provided by the
and can be changed in the `FpConfig.h` header.  These types are described in the
[numerical types design document](../../reference/numerical-types.md).

The above document also describes the methods for configuring the configurable types used to adjust various fprime
types.

### IEEE 754 compliance of the floating point implementation

> [!NOTE]
> this configuration is performed in the `PlatformTypes.h` header as it is platform dependent and not project dependent.

Some industrial coding rules for safety and critical systems require floating point implementations to conform to a
defined floating point standard, such as IEEE 754. The reason for this is that if the implementation does not conform to
a standard, it can lead to problems with the accuracy and reliability of calculations.

By default, F´ checks for IEEE754 compliant floating point arithmetic at compile time. However, if a user does not have
a C++11 implementation on their platform that supports IEEE754 floating point arithmetic, an option is provided to
bypass this check:

| Macro                           | Definition                                                       | Default | Valid Values   |
| --------------------------------| -----------------------------------------------------------------|---------|----------------|
| SKIP_FLOAT_IEEE_754_COMPLIANCE  | Skip IEEE 754 compliance check of floating point implementation. | 0 (off) | 0 (off) 1 (on) |


#### Time Base and Time Context

The F′ time tags have a field that specifies the time base of the time tag. A time base is defined as a clock in the
system correlated with a known epoch. It is often the case that when a system is being initialized, it does not always
have access to a clock correlated to external operations. It can transition through several time bases (processor,
radio, Earth) on the way to becoming fully operational. The TimeBase type defines the set of clocks in the system that
can produce a time tag. It lets users of the system see which clock was used when time tagging telemetry.

Time contexts are another value associated with time. By default time context is NOT used in Time comparisons, in
other words Times having the same TimeBase are comparable regardless of what the context value is set to. This also
means by default when doing mathematical operations on Fw:Time objects (i.e. add, subtract), by default it is NOT
checked that the time contexts match. If they do match, math results will preserve the (matching) time context,
otherwise it will be set to 0.

Time base and time context are now always used in the Fw::Time class implementation. The TimeBase enum defines the
possible time base values used by the system and is set in the FpConfig.fpp file.

The following time base options are required:

| Enum | Description |
|------|-------------|
| TB_NONE | No time base has been established |
| TB_WORKSTATION_TIME | Time as reported on workstation where software is running. For testing. |
| TB_DONT_CARE | Don't care value for sequences. If FwTimeBaseStoreType is changed, value should be changed |


### Object Settings

The architecture allows for various settings to control, monitor, and trace objects in the system. These settings
typically result in a larger binary size but make the framework and system easier to debug. This section includes
a discussion of OS objects like Tasks and Queues as well.

#### Object Naming

The architecture can store names for each object created. This is useful when using object registries or tracing to see
what objects exist and how they interact. The object naming does increase the per-object storage and code size, so in a
resource-constrained environment, disabling this feature might be desirable. This macro should be used in developer
implementation classes to call the correct constructor in the code-generated base classes. Table 35 provides the
macros related to this feature.

The `Os::Queue` class stores a queue name as private data. Table 35 provides the macro for this feature. The `Os::Task`
class stores a task name as private data. Table 35 provides the macro for this feature as well.

**Table 35.** Macros for object naming, queue naming, and task naming

| Macro                     | Definition                                  | Default | Valid Values      |
|---------------------------| ------------------------------------------- |---------|-------------------|
| FW_OBJECT_NAMES           | Enables storage and retrieval of the name   | 1 (on)  | 0 (off) 1 (on)    |
| FW_OBJ_NAME_BUFFER_SIZE   | Size of the buffer storing the object name  | 80      | Positive integer  |
| FW_QUEUE_NAME_BUFFER_SIZE | Size of the buffer storing the queue names  | 80      | Positive integer  |
| FW_TASK_NAME_BUFFER_SIZE  | Size of the buffer storing task names       | 80      | Positive integer  |

> [!NOTE]
> The macro `FW_OPTIONAL_NAME("string")` can be used to conditionally return the given string or an empty string depending on whether `FW_OBJECT_NAMES` is on. This can be used to strip out component names from code when building without `FW_OBJECT_NAMES`.

> [!NOTE]
> If the size of the string passed to the code-generated component base classes is larger than this size, the string will be truncated. `FW_OBJECT_NAMES` must be turned on for `FW_OBJ_NAME_BUFFER_SIZE` to have any effect.

> [!NOTE]
> `FW_QUEUE_NAME_BUFFER_SIZE` and `FW_TASK_NAME_BUFFER_SIZE` are only used if `FW_OBJECT_NAMES` is **turned off**. Otherwise, the supplied object name is used.

#### Object to String

The framework port and object classes have an optional `toString()` method. This method by default returns the instance
name of the object, but `toString()` is defined as a virtual method so a developer class can override this and provide
custom information. Table 36 provides the macros to configure this feature.

> [!NOTE]
> For these settings to work `FW_OBJECT_NAMES` must be turned on.

**Table 36.** Macros for object to string.

| Macro                                 | Definition                                                  | Default | Valid Values      |
| ------------------------------------- | ----------------------------------------------------------- |---------|-------------------|
| FW_OBJECT_TO_STRING                   | Enables the toString() method                               | 1 (on)  | 0 (off) 1 (on)    |
| FW_OBJ_TO_STRING_BUFFER_SIZE          | Defines buffer size used to store toString() results        | 255     | Positive integer  |
| FW_SERIALIZABLE_TO_STRING             | Defines a toString() method for code-generated serializable | 1 (on)  | 0 (off) 1 (on)    |
| FW_SERIALIZABLE_TO_STRING_BUFFER_SIZE | Defines buffer size of toString() result for serializables  | 255     | Positive integer  |
| FW_ARRAY_TO_STRING                    | Defines a toString() method for code-generated arrays       | 1 (on)  | 0 (off) 1 (on)    |
| FW_ARRAY_TO_STRING_BUFFER_SIZE        | Defines buffer size of toString() result for arrays         | 256     | Positive integer  |


#### Object Registry

An object registry is a class that holds a list of framework component and port objects. The registry can be used to
list all the objects, or call common functions on all objects. A base class for the object registry is defined in
`Fw/Obj/ObjBase.hpp`, and a simple implementation can be found in `Fw/Obj/SimpleObjRegistry.hpp`.
Table 37 provides the macros to configure this feature. Message queues allow for their own registration such that the
project may track them as well.

**Table 37.** Macros for object
registry.

| Macro                         | Definition                                                                  | Default | Valid Values      |
| ----------------------------- | ----------------------------------------------------------------------------|---------|-------------------|
| FW_OBJECT_REGISTRATION        | Enables object registries.                                                  | 1 (on)  | 0 (off) 1 (on)    |
| FW_OBJ_SIMPLE_REG_ENTRIES     | The size of the array in the simple object registry used to store objects.  | 500     | Positive integer  |
| FW_OBJ_SIMPLE_REG_BUFF_SIZE   | The size of the buffer used to store object names in the simple registry.   | 255     | Positive integer  |
| FW_QUEUE_REGISTRATION         | Enables queue registries.                                                   | 1 (on)  | 0 (off) 1 (on)    |
| FW_QUEUE_SIMPLE_QUEUE_ENTRIES | The size of the array in the simple object registry used to store queues.   | 100     | Positive integer  |

> [!NOTE]
> `FW_OBJECT_REGISTRATION` must be turned on for `FW_OBJ_SIMPLE_REG_ENTRIES` and `FW_OBJ_SIMPLE_REG_BUFF_SIZE` to have any effect.

> [!NOTE]
> See table 35 for configuring queue name sizes.


### Asserts

The assert feature is described in [F´ Asserts](assert.md). This configuration allows a project to turn asserts off,
use hash IDs for the assert message, or use full filenames for the assert message. Table 38 provides ways that asserts
can be configured.

**Table 38.** Macros for assert.

| Macro                  | Definition                       |                                                                    | Default            |
| ---------------------- | ---------------------------------| -------------------------------------------------------------------|--------------------|
| FW_ASSERT_LEVEL        | Sets the assert report level to: |                                                                    | FW_FILENAME_ASSERT |
|                        | **Value**                        | **Definition**                                                     |                    |
|                        | FW_NO_ASSERT                     | Asserts turned off, removing all assert code.                      |                    |
|                        | FW_FILEID_ASSERT                 | Asserts turned on, hash value used in place of __FILE__ on message |                    |
|                        | FW_FILENAME_ASSERT               | Asserts turned on, __FILE__ macro is used in the assert message    |                    |
| FW_ASSERT_TEXT_SIZE    | The buffer size used to store the assert message  |                                                   | 120                |

Setting assert level `FW_FILEID_ASSERT`  saves a lot of code space since no file name is stored. The make system
supplies this to the compiler by hashing the file name. The original filename can be recovered by running
`fprime-util hash-to-file <hash>`.

Setting assert level to `FW_ASSERT_TEXT_SIZE` can ease debugging asserts, but typically `FW_ASSERT_TEXT_SIZE` must be
increased as most file name paths are longer than 120.


### Port Tracing

When components are interconnected, it is often useful to trace the set of invocations through components and ports. The
port base class has a `trace()` call that is invoked by the derived port classes whenever the port is invoked. The
`trace()` calls `Os::Log::log()` with the name of the port once the port base class method `setTrace()` has been called.
Individual ports can have tracing turned on and off by calling the `overrideTrace()` method on the port instance.
Table 39 provides the macro to configure this feature.

**Table 39.** Macro for port tracing.


| Macro             | Definition            | Default | Valid Values      |
| ----------------- | --------------------- |---------|-------------------|
| FW_PORT_TRACING   | Enables port tracing. | 1 (on)  | 0 (off) 1 (on)    |

### Port Serialization

As discussed in the user guide, a port type (Input/OutputSerializePort) exists that has no interface type, but instead
receives (or sends) a serialized form of the port invocation for the attached port. The primary pattern for this is to
invoke components on remote nodes. The code generator generates code in each port that will serialize or deserialize the
invocation if it detects that it is connected to a serializing port. If development is for a single node, this feature
can be disabled to reduce the code size. Table 40 provides the macro to configure this feature.

**Table 40.** Macro for port serialization.

| Macro                   | Definition                  | Default | Valid Values      |
| ----------------------- | --------------------------- |---------|-------------------|
| FW_PORT_SERIALIZATION   | Enables port serialization. | 1 (on)  | 0 (off) 1 (on)    |

### Serializable Type ID

As described [in serializable types](../overview/05-enum-arr-ser.md), serializable types can be defined for use in the code.
When objects of those types are serialized, an integer representing the type ID can be serialized along with the object
data. This allows the type to be determined later if only the serialized form is available. Turning off this feature
will lower the amount of data moved around for a given object when it is serialized. Table 41 provides
the macros to configure this feature.


**Table 41.** Macros for serializable type ID.

| Macro                          | Definition                       | Default | Valid Values      |
| -------------------------------| ---------------------------------|---------|-------------------|
| FW_SERIALIZATION_TYPE_ID       | Enables serializing the type ID  | 0 (off) | 0 (off) 1 (on)    |
| FW_SERIALIZATION_TYPE_ID_BYTES | Defines size of serialization ID | 4       | 1 - 4             |

> [!NOTE]
> Smaller values for `FW_SERIALIZATION_TYPE_ID_BYTES` means that less data storage is needed, but also limits the number of types that can be defined. `FW_SERIALIZATION_TYPE_ID` is required to have type IDs in the buffer and thus to introspect what type is contained in the buffer.


### Buffer Sizes

Many of the built-in F´ data types define buffer sizes that allow them to be passed as a com buffer type, sent out
through the ground interface, serialized, and more. This section will discuss the com buffer configuration,
command, channel, event, parameter, and other buffer size arguments.

The com buffer must be able to store all the other types such that they can all be passed as generic communication. Thus
`FW_COM_BUFFER_MAX_SIZE` must be large enough to hold each buffer size **and** the header data for each type. Thus these
settings are typically derived and this is done by default.

> [!WARNING]
> only modify the comm buffer size to ensure that there will be no faults in the system.

In all cases, these definitions are global for each type in the system. Thus the buffer **must** be large enough to
hold the data for the largest of a given type in the system.  An assert will result if the buffer is set too small. i.e.
the `FW_CMD_ARG_BUFFER_MAX_SIZE` cannot be smaller than the serialized size of the command with the largest arguments.

These types also provide optional string sizes for their constituent pieces. However, the `MAX_STRING_SIZE` settings must
**always** be smaller than the `BUFFER_MAX_SIZE`. i.e. the command string max size cannot be larger than the command
buffer max size, as the string is serialized into the buffer.

Commands serialize argument values into these buffers. Events (aka log events) also serialize just the arguments.
Channelized telemetry and parameters serialize the values. Other information like event strings is not serialized but
rather reconstructed when needed from the dictionary. This is all placed in a comm buffer.

Table 42 provides the macros to configure these features.

**Table 42.** Macros for buffers.

| Macro                           | Definition                                            | Default | Valid Values     |
| ------------------------------- | ------------------------------------------------------|---------|------------------|
| FW_COM_BUFFER_MAX_SIZE          | Defines the size of a com buffer                      | 128     | Positive integer |
| FW_CMD_ARG_BUFFER_MAX_SIZE      | Defines the size of command argument buffers          | Derived |                  |
| FW_CMD_STRING_MAX_SIZE          | Defines the maximum size of a command string argument | 40      |                  |
| FW_LOG_BUFFER_MAX_SIZE          | Defines the size of event buffers                     | Derived |                  |
| FW_LOG_STRING_MAX_SIZE          | Defines the maximum size of an event string argument  | 100     |                  |
| FW_TLM_BUFFER_MAX_SIZE          | Defines the size of telemetry channel buffers         | Derived |                  |
| FW_TLM_STRING_MAX_SIZE          | Defines the maximum size of a channel string value    | 40      |                  |
| FW_PRM_BUFFER_MAX_SIZE          | Defines the size of parameter buffers                 | Derived |                  |
| FW_PRM_STRING_MAX_SIZE          | Defines the maximum size of a parameter string value  | 40      |                  |

Other Buffers are defined in the system for specific purposes. These do not need to fit inside a comm buffer, and thus
are less restrictive in size.

| Macro                      | Definition                                                 | Default | Valid Values     |
| -------------------------- | -----------------------------------------------------------|---------|------------------|
| FW_FILE_BUFFER_MAX_SIZE    | Defines buffer and chunk size for file uplink and downlink | `FW_COM_BUFFER_MAX_SIZE`     | Positive integer |
| FW_INTERNAL_INTERFACE_STRING_MAX_SIZE | Maximum size for interface string               | 40      | Positive integer |

### Text Logging

Event functions that are called are turned into two output port calls. One is a binary port that is used to store the
event to be transported to ground software or a testing interface external to the software. The component also takes
the format string specified in the FPP and populates it with the event arguments, and calls an output port with a
readable text version of the event. This is meant to be used for a console interface so the user can see, in text form,
the same events being stored for transmission. A component with the text logging input port can be used to display the
text. A very simple implementation of this can be seen in `Svc/PassiveConsoleTextLogger`. In a resource-constrained
environment or in a flight implementation where the console is not viewable, the text formatting and extra code can
consume an undesirable number of processor cycles. For this reason, the text logging can be turned off via a macro. This
compiles out the code and format strings for text logging. Table 46 provides the macros to configure text logging.

**Table 46.** Macros for text logging.

| Macro                       | Definition                                              | Default | Valid Values     |
| --------------------------- | --------------------------------------------------------|---------|------------------|
| FW_ENABLE_TEXT_LOGGING      | Enables or disables text logging                        | 1 (on)  | 0 (off) 1 (on)   |
| FW_LOG_TEXT_BUFFER_SIZE     | Maximum size of the textual representation of the event | 256     | Positive integer |

> [!NOTE]
> The `FW_LOG_TEXT_BUFFER_SIZE` should be large enough to store the full event including its text format string after being populated with arguments.


### Misc Configuration Settings

This setting describes some of the other settings available in `FpConfig.hpp` and did not fit in other sections. These
are described in the tables below.

Table 47 describes other user settings.

**Table 47.** Misc macros available to the user.

| Macro                       | Definition                                              | Default | Valid Values     |
| --------------------------- | --------------------------------------------------------|---------|------------------|
| FW_CMD_CHECK_RESIDUAL       | Enables command serialization extra bytes check         | 1 (on)  | 0 (off) 1 (on)   |
| FW_AMPCS_COMPATIBLE         | Adds argument sizes to event argument serialization     | 0 (off) | 0 (off) 1 (on)   |

> [!NOTE]
> Normally when a command is deserialized, the handler checks to see if there are any leftover bytes in the buffer. If there are, it assumes that the command was corrupted somehow since the serialized size should match the serialized size of the argument list. In some cases, command buffers are padded so the data can be larger than the serialized size of the command. Turning `FW_CMD_CHECK_RESIDUAL` off can disable this check and allow leftover bytes.

> [!NOTE]
> Some ground systems require the size of the event argument to be serialized into the buffer instead of predicting the size using the dictionary. Setting `FW_AMPCS_COMPATIBLE` will serialize these sizes into the event buffers **and** break compatibility with the F´ ground system as it does not use this feature.

> [!NOTE]
> The following settings are defined by the build system and are in `FpConfig.hpp` to provide a default off value. These must be set by the build system as the setting works in unison with other modules that the build system includes when enabling these settings.

## Component Configuration

Component configurations are also provided as part of the project's config directory. If the directory is not provided,
then the default from the framework is used. **Remember:** if the project overrides any configuration, that new
directory must contain all the component headers as well as the `FpConfig.hpp` as C++ prevents including individual
headers.

These component headers follow the form `<Component>Cfg.hpp` and allows a project to set the configuration for each
component's C++ implementation. This is typically to set maximum sizes for tables, and other static memory allocations.
Some components allow users to turn on and off features. If a component does not have a header, it has no configuration
for the user to set.

Users are encouraged to look through the header for the component of interest as they should be self-descriptive.

## Conclusion

The user should now have a very detailed understanding of how to configure F´. Although there are some automatic checks
built into F´ to check for some invalid configurations, the user should take care to understand the implication of
changes to these settings. The F´ team sincerely hopes this bombardment of information will prove useful.