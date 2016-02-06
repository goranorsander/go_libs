//
//  observable_object_test_suite_wstring.cpp
//
//  Copyright 2015 G�ran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <functional>
#include <string>

#include <gtest/gtest.h>

#include <go/mvvm.hpp>
#include <go/property.hpp>

namespace m = go::mvvm;
namespace p = go::property;
namespace ph = std::placeholders;

// Test observable_object
class product_model
    : public m::observable_object<std::wstring>
{
public:
    ~product_model()
    {
    }

private:
    product_model(const product_model&) = delete;

public:
    product_model()
        : m::observable_object<std::wstring>()
        , _product_id(0)
        , _product_name()
        , _unit_price(0.0)
        , product_id(L"product_id", std::bind(&product_model::get_product_id, this), std::bind(&product_model::set_product_id, this, ph::_1))
        , product_name(L"product_name", std::bind(&product_model::get_product_name, this), std::bind(&product_model::set_product_name, this, ph::_1))
        , unit_price(L"unit_price", std::bind(&product_model::get_unit_price, this), std::bind(&product_model::set_unit_price, this, ph::_1))
    {
    }

public:
    p::property<int, std::wstring> product_id;
    p::property<std::wstring, std::wstring> product_name;
    p::property<double, std::wstring> unit_price;

private:
    int get_product_id() const
    {
        return _product_id;
    }

    void set_product_id(const int& v)
    {
        if(v != _product_id)
        {
            _product_id = v;
            on_property_changed(L"product_id");
        }
    }

    std::wstring get_product_name() const
    {
        return _product_name;
    }

    void set_product_name(const std::wstring& v)
    {
        if(v != _product_name)
        {
            _product_name = v;
            on_property_changed(L"product_name");
        }
    }

    double get_unit_price() const
    {
        return _unit_price;
    }

    void set_unit_price(const double& v)
    {
        if(v != _unit_price)
        {
            _unit_price = v;
            on_property_changed(L"unit_price");
        }
    }

private:
    int _product_id;
    std::wstring _product_name;
    double _unit_price;
};

class product_model_observer
{
public:
    ~product_model_observer()
    {
    }

    product_model_observer()
        : _on_property_changed_slot_key(0)
        , _product_id_change_count(0)
        , _product_name_change_count(0)
        , _unit_price_change_count(0)
    {
    }

    void connect(product_model& m)
    {
        _on_property_changed_slot_key = m.property_changed.connect(std::bind(&product_model_observer::on_property_changed, this, ph::_1, ph::_2));
    }

    void disconnect(product_model& m)
    {
        m.property_changed.disconnect(_on_property_changed_slot_key);
    }

    void on_property_changed(const m::object::ptr& o, const m::property_changed_arguments<std::wstring>::ptr& a)
    {
        if(o && a)
        {
            if(a->property_name() == L"product_id") { ++_product_id_change_count; }
            else if(a->property_name() == L"product_name") { ++_product_name_change_count; }
            else if(a->property_name() == L"unit_price") { ++_unit_price_change_count; }
        }
    }

    int product_id_change_count() const { return _product_id_change_count; }
    int product_name_change_count() const { return _product_name_change_count; }
    int unit_price_change_count() const { return _unit_price_change_count; }

private:
    m::slot_key_type _on_property_changed_slot_key;
    int _product_id_change_count;
    int _product_name_change_count;
    int _unit_price_change_count;
};

TEST(observable_object_test_suite_wstring, test_observable_object)
{
    std::shared_ptr<product_model> m(new product_model);
    product_model_observer o;

    o.connect(*m);

    // After connect
    EXPECT_EQ(0, o.product_id_change_count());
    EXPECT_EQ(0, o.product_name_change_count());
    EXPECT_EQ(0, o.unit_price_change_count());

    m->product_id = 47;

    // After one assignment
    EXPECT_EQ(1, o.product_id_change_count());
    EXPECT_EQ(0, o.product_name_change_count());
    EXPECT_EQ(0, o.unit_price_change_count());

    int pid = m->product_id;

    // After one access
    EXPECT_EQ(47, pid);
    EXPECT_EQ(1, o.product_id_change_count());
    EXPECT_EQ(0, o.product_name_change_count());
    EXPECT_EQ(0, o.unit_price_change_count());

    m->product_id = 47;
    pid = m->product_id;

    // After assignment of same value
    EXPECT_EQ(47, pid);
    EXPECT_EQ(1, o.product_id_change_count());
    EXPECT_EQ(0, o.product_name_change_count());
    EXPECT_EQ(0, o.unit_price_change_count());

    o.disconnect(*m);
    m->product_id = 74;
    pid = m->product_id;

    // After disconnect and assignment of new value
    EXPECT_EQ(74, pid);
    EXPECT_EQ(1, o.product_id_change_count());
    EXPECT_EQ(0, o.product_name_change_count());
    EXPECT_EQ(0, o.unit_price_change_count());
}
