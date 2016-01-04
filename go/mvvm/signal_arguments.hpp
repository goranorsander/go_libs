#ifndef GO_MVVM_SIGNAL_ARGUMENTS_HPP_INCLUDED
#define GO_MVVM_SIGNAL_ARGUMENTS_HPP_INCLUDED

//
//  signal_arguments.hpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

//#include <boost/noncopyable.hpp>
//#include <boost/shared_ptr.hpp>

namespace go
{
namespace mvvm
{

class signal_arguments
    : private boost::noncopyable 
{
public:
    typedef boost::shared_ptr<signal_arguments> ptr;

public:
    virtual ~signal_arguments() = 0
    {
    }

protected:
    signal_arguments()
    {
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_SIGNAL_ARGUMENTS_HPP_INCLUDED
