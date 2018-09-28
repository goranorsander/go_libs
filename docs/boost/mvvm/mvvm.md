---
layout: boost_lib_mvvm
---

```c++
namespace go_boost::mvvm
```

# GO Boost MVVM Library

```c++
<go_boost/mvvm.hpp>
```

## Description

**MVVM**

Model–View–ViewModel (MVVM) is a software architectural pattern primarily intended for
development of the graphical user interface (GUI) applications. MVVM favours separation
of development of the user interface from development of the business logic. The three
main components in MVVM are:

* **Model** - a Model contains some aspect of your business logic. That is all a model
does. Typically a model is a class object that hold data or serve as a proxy for some
persistent storage. It has nothing to do with the user interface and couples to neither
the View nor the ViewModel.
* **ViewModel** - a ViewModel contains the presentational logic. It couples to the Model, 
preferably using an interface. The ViewModel does most of the magic. It will deal with
data access, complex calculations, business rules, validation, user interaction, etc.
* **View** - a View is the user interface that present data. Most often it is a GUI
(Graphical User Interface) but it can just as well be a command line interface. The View
use data binding to the ViewModel to populate its UI controls.

The concept of data- and command-binding is essential. MVVM make use of binding to better
facilitate the separation of View development from ViewModel and Model development, by
removing virtually all UI code (known as the "code-behind") from the View. Binding rely
on properties and the concept of data context. Other important components are value
converters, events, and commands.

## Library architecture

The **GO Boost MVVM Library** use the [factory method pattern](https://en.wikipedia.org/wiki/Factory_method_pattern)
extensively. Most classes will have one or more static **create** methods in combination
with protected or private constructors.

## Reference

### Nested namespaces

* [iterator](./iterator/iterator.html)
* [utility](./utility/utility.html)

### Class reference

#### Interfaces

* [basic_command_execution_observer_interface](./class_template_basic_command_execution_observer_interface.html)
  * [command_execution_observer_interface](./class_template_basic_command_execution_observer_interface.html)
  * [wcommand_execution_wobserver_interface](./class_template_basic_command_execution_observer_interface.html)
* [basic_command_interface](./class_template_basic_command_interface.html)
  * [command_interface](./class_template_basic_command_interface.html)
  * [wcommand_interface](./class_template_basic_command_interface.html)
* [data_context_interface](./class_template_data_context_interface.html)
* [basic_event_firing_observer_interface](./class_template_basic_event_firing_observer_interface.html)
  * [event_firing_observer_interface](./class_template_basic_event_firing_observer_interface.html)
  * [wevent_firing_observer_interface](./class_template_basic_event_firing_observer_interface.html)
* [basic_notify_command_execution_interface](./class_template_basic_notify_command_execution_interface.html)
  * [notify_command_execution_interface](./class_template_basic_notify_command_execution_interface.html)
  * [notify_wcommand_execution_interface](./class_template_basic_notify_command_execution_interface.html)
* [notify_container_changed_interface](./class_notify_container_changed_interface.html)
* [notify_data_context_change_interface](./class_notify_data_context_change_interface.html)
* [basic_notify_event_firing_interface](./class_template_basic_notify_event_firing_interface.html)
  * [notify_event_firing_interface](./class_template_basic_notify_event_firing_interface.html)
  * [notify_wevent_firing_interface](./class_template_basic_notify_event_firing_interface.html)
* [basic_notify_property_changed_interface](./class_template_basic_notify_property_changed_interface.html)
  * [notify_property_changed_interface](./class_template_basic_notify_property_changed_interface.html)
  * [notify_wproperty_changed_interface](./class_template_basic_notify_property_changed_interface.html)
* [notify_view_model_change_interface](./class_notify_view_model_change_interface.html)
* [basic_object_observer_interface](./class_template_basic_object_observer_interface.html)
  * [object_observer_interface](./class_template_basic_object_observer_interface.html)
  * [object_wobserver_interface](./class_template_basic_object_observer_interface.html)
* [view_model_interface](./class_view_model_interface.html)

#### Managers

* [basic_command_manager](./class_template_basic_command_manager.html)
  * [command_manager](./class_template_basic_command_manager.html)
  * [wcommand_manager](./class_template_basic_command_manager.html)
* [basic_event_manager](./class_template_basic_event_manager.html)
  * [event_manager](./class_template_basic_event_manager.html)
  * [wevent_manager](./class_template_basic_event_manager.html)

#### Commands

* [command_parameters](./class_command_parameters.html)
* [basic_relay_command](./class_template_basic_relay_command.html)
  * [relay_command](./class_template_basic_relay_command.html)
  * [relay_wcommand](./class_template_basic_relay_command.html)

#### Events

* [container_changed_arguments](./class_container_changed_arguments.html)
* [data_context_changed_arguments](./class_data_context_changed_arguments.html)
* [data_context_will_change_arguments](./class_data_context_will_change_arguments.html)
* [basic_event](./class_template_basic_event.html)
  * [event](./class_template_basic_event.html)
  * [wevent](./class_template_basic_event.html)
* [notify_container_changed_action](./enum_notify_container_changed_action.html)
* [basic_property_changed_arguments](./class_template_basic_property_changed_arguments.html)
  * [property_changed_arguments](./class_template_basic_property_changed_arguments.html)
  * [wproperty_changed_arguments](./class_template_basic_property_changed_arguments.html)
* [view_model_changed_arguments](./class_view_model_changed_arguments.html)
* [view_model_will_change_arguments](./class_view_model_will_change_arguments.html)

#### Objects

* [basic_observable_object](./class_template_basic_observable_object.html)
  * [observable_object](./class_template_basic_observable_object.html)
  * [wobservable_object](./class_template_basic_observable_object.html)
* [object](./class_object.html)

#### Observable containers

* [basic_observable_container](./class_template_basic_observable_container.html)
* [basic_observable_associative_container](./class_template_basic_observable_associative_container.html)
* [basic_observable_ordered_associative_container](./class_template_basic_observable_ordered_associative_container.html)
* [basic_observable_sequence_container](./class_template_basic_observable_sequence_container.html)
* [basic_observable_unordered_associative_container](./class_template_basic_observable_unordered_associative_container.html)

**Sequence containers**

* [basic_observable_array](./class_template_basic_observable_array.html)
  * [observable_array](./class_template_basic_observable_array.html)
  * [wobservable_array](./class_template_basic_observable_array.html)
* [basic_observable_deque](./class_template_basic_observable_deque.html)
  * [observable_deque](./class_template_basic_observable_deque.html)
  * [wobservable_deque](./class_template_basic_observable_deque.html)
* [basic_observable_forward_list](./class_template_basic_observable_forward_list.html)
  * [observable_forward_list](./class_template_basic_observable_forward_list.html)
  * [wobservable_forward_list](./class_template_basic_observable_forward_list.html)
* [basic_observable_list](./class_template_basic_observable_list.html)
  * [observable_list](./class_template_basic_observable_list.html)
  * [wobservable_list](./class_template_basic_observable_list.html)
* [basic_observable_vector](./class_template_basic_observable_vector.html)
  * [observable_vector](./class_template_basic_observable_vector.html)
  * [wobservable_vector](./class_template_basic_observable_vector.html)

**Associative containers**

* [basic_observable_map](./class_template_basic_observable_map.html)
  * [observable_map](./class_template_basic_observable_map.html)
  * [wobservable_map](./class_template_basic_observable_map.html)
* [basic_observable_multimap](./class_template_basic_observable_multimap.html)
  * [observable_multimap](./class_template_basic_observable_multimap.html)
  * [wobservable_multimap](./class_template_basic_observable_multimap.html)
* [basic_observable_multiset](./class_template_basic_observable_multiset.html)
  * [observable_multiset](./class_template_basic_observable_multiset.html)
  * [wobservable_multiset](./class_template_basic_observable_multiset.html)
* [basic_observable_set](./class_template_basic_observable_set.html)
  * [observable_set](./class_template_basic_observable_set.html)
  * [wobservable_set](./class_template_basic_observable_set.html)
* [basic_observable_unordered_map](./class_template_basic_observable_unordered_map.html)
  * [observable_unordered_map](./class_template_basic_observable_unordered_map.html)
  * [wobservable_unordered_map](./class_template_basic_observable_unordered_map.html)
* [basic_observable_unordered_multimap](./class_template_basic_observable_unordered_multimap.html)
  * [observable_unordered_multimap](./class_template_basic_observable_unordered_multimap.html)
  * [wobservable_unordered_multimap](./class_template_basic_observable_unordered_multimap.html)
* [basic_observable_unordered_multiset](./class_template_basic_observable_unordered_multiset.html)
  * [observable_unordered_multiset](./class_template_basic_observable_unordered_multiset.html)
  * [wobservable_unordered_multiset](./class_template_basic_observable_unordered_multiset.html)
* [basic_observable_unordered_set](./class_template_basic_observable_unordered_set.html)
  * [observable_unordered_set](./class_template_basic_observable_unordered_set.html)
  * [wobservable_unordered_set](./class_template_basic_observable_unordered_set.html)
