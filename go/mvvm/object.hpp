#ifndef GO_MVVM_OBJECT_HPP_INCLUDED
#define GO_MVVM_OBJECT_HPP_INCLUDED

//
//  object.hpp
//
//  Copyright 2015 G�ran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

//#include <boost/enable_shared_from_this.hpp>

namespace go
{
namespace mvvm
{

class object
    : public enable_shared_from_this<object>
{
public:
    typedef boost::shared_ptr<object> ptr;

public:
    virtual ~object() = 0
    {
    }

protected:
    object()
        : enable_shared_from_this<object>()
    {
    }
};

} // namespace mvvm
} // namespace go

#endif  // #ifndef GO_MVVM_OBJECT_HPP_INCLUDED
