---
layout: boost_lib_diagnostics_benchmark
---

```c++
namespace go_boost::diagnostics::benchmark
```

# class template basic_stopwatch

```c++
<go_boost/diagnostics/stopwatch.hpp>
```

The **basic_stopwatch** is a generalization class for properties with any value type and
name string class. It is implemented using the proxy storage policy.

It is declared as:

```c++
template<class C, class D>
class basic_stopwatch
{
public:
    virtual ~basic_stopwatch() = default;
    basic_stopwatch();
    basic_stopwatch(const basic_stopwatch& other) = default;
    basic_stopwatch(basic_stopwatch&& other) = default;

    this_type& operator=(const this_type&) = default;
    this_type& operator=(this_type&&) = default;

    void start();
    void stop();
    void reset() noexcept;
    constexpr bool started() const noexcept;
    constexpr duration_type last_duration() const noexcept;
    constexpr duration_type total_duration() const noexcept;
    constexpr duration_type average_duration() const noexcept;
    constexpr count_type count() const noexcept;
};
```

## Template parameters

Parameter | Description
-|-
C | The clock class
D | The duration class

## Member types

Member type | Definition
-|-
clock_type | C
duration_type | D
this_type | basic_stopwatch<C, D>
time_point_type | std\::chrono\::time_point<C>
count_type | std\::size_t

## Member functions

### Destructor

Specifiers |
-|
public virtual |

Destroys the **basic_stopwatch** object.

### Constructor

Constructor | Specifiers | Signature
-|-|-
*default (1)* | public | basic_stopwatch()
*copy (1)* | public | basic_stopwatch(const basic_stopwatch& other)
*move (1)* | public | basic_stopwatch(basic_stopwatch&& other)

1. Constructs a **basic_stopwatch** object.
2. Constructs a **basic_stopwatch** object with the copy of the contents of **other**.
3. Constructs a **basic_stopwatch** object with the contents of **other** using move semantics.

### Assignment operator

Operator | Specifiers | Signature
-|-
*assign copy (1)* | public | basic_stopwatch& operator=(const basic_stopwatch& other)
*assign move (2)* | public | basic_stopwatch& operator=(basic_stopwatch&& other)

1. Copies an **basic_stopwatch** object.
2. Copies an **basic_stopwatch** object using move semantics.

### start

Specifiers | Signature
-|-
public | void start()

Start the stopwatch.

### stop

Specifiers | Signature
-|-
public | void stop()

Stop the stopwatch.

### reset

Specifiers | Signature
-|-
public | void reset() noexcept

Reset the stopwatch.

### started

Specifiers | Signature
-|-
public constexpr | bool started() const noexcept

Return **true** if the stopwatch is started, **false** otherwise.

### last_duration

Specifiers | Signature
-|-
public constexpr | duration_type last_duration() const noexcept

Return the last duration, i.e. the time between the last **start**
and **stop** command sequence.

### total_duration

Specifiers | Signature
-|-
public constexpr | duration_type total_duration() const noexcept

Return the total duration, i.e. the acumulated time between all **start**
and **stop** command sequences since the stopwatch was created or reset.

### average_duration

Specifiers | Signature
-|-
public constexpr | duration_type average_duration() const noexcept

Return the average duration, i.e. the acumulated time between all **start**
and **stop** command sequences since the stopwatch was created or reset divided
by the number of **start** and **stop** command sequences.

### count

Specifiers | Signature
-|-
public constexpr | count_type count() const noexcept

The number of **start** and **stop** command sequences since the stopwatch was
created or reset.

# class template basic_stopwatch specializations

## typedef stopwatch

The **stopwatch** is a type definition for a stopwatch using the high-resolution
clock and a microsecond duration.

It is defined as:

```c++
typedef basic_stopwatch<boost::chrono::high_resolution_clock, boost::chrono::microseconds> stopwatch;
```
