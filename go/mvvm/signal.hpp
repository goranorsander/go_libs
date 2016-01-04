#ifndef GO_MVVM_SIGNAL_HPP_INCLUDED
#define GO_MVVM_SIGNAL_HPP_INCLUDED

//
//  signal.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

namespace go
{
namespace mvvm
{

class signal
{
public:
    typedef boost::shared_ptr<signal> ptr;

public:
    virtual ~signal() = 0
    {
    }

protected:
    signal()
    {
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_SIGNAL_HPP_INCLUDED
