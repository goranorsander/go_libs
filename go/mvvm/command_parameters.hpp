#ifndef GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
#define GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED

//
//  command_parameters.hpp
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

class command_parameters
    : public boost::noncopyable
{
public:
    typedef boost::shared_ptr<command_parameters> ptr;

public:
    virtual ~command_parameters()
    {
    }

protected:
    command_parameters()
        : boost::noncopyable()
    {
    }

public:
    static ptr create()
    {
        return ptr(new command_parameters());
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_COMMAND_PARAMETERS_HPP_INCLUDED
