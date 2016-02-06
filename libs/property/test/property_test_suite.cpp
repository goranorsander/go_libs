//
//  properties_test_suite.cpp
//
//  Copyright 2015 Göran Orsander
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <functional>
#include <string>

#include <gtest/gtest.h>

#include <go/property.hpp>

namespace p = go::property;
namespace ph = std::placeholders;

// Test value_scalar_property
class camera
{
public:
    p::value_scalar_property<int> width;
    p::value_scalar_property<double> height;
    p::value_scalar_property<std::string> name;

    camera()
        : width(std::string("width"), 320)
        , height(std::string("height"), 200.0)
        , name(std::string("name"), std::string("camera"))
    {
    }

    camera(const camera& v)
        : width(v.width)
        , height(v.height)
        , name(v.name)
    {
    }

    camera& operator=(const camera& v)
    {
        width = v.width;
        height = v.height;
        name = v.name;
    }
};

TEST(properties_test_suite, value_scalar_properties)
{
    camera c;

    // Method oriented get
    EXPECT_EQ(320, c.width());
    EXPECT_EQ(200.0, c.height());
    EXPECT_EQ(std::string("camera"), c.name());

    // Cast operator oriented get
    EXPECT_EQ(320, static_cast<int>(c.width));
    EXPECT_EQ(200.0, static_cast<double>(c.height));
    EXPECT_EQ(std::string("camera"), static_cast<std::string>(c.name));

    // Implicit cast oriented get
    EXPECT_TRUE(320 == c.width);
    EXPECT_TRUE(200.0 == c.height);
    EXPECT_TRUE(std::string("camera") == c.name);

    // Traditional get
    EXPECT_EQ(320, c.width.get());
    EXPECT_EQ(200.0, c.height.get());
    EXPECT_EQ(std::string("camera"), c.name.get());

    // Method oriented set
    c.width(480);
    c.height(340.0);
    c.name("Camera 2");
    EXPECT_EQ(480, c.width());
    EXPECT_EQ(340.0, c.height());
    EXPECT_EQ(std::string("Camera 2"), c.name());

    // Assign operator oriented set
    c.width = 560;
    c.height = 410.0;
    c.name = std::string("CAMERA 3");
    EXPECT_EQ(560, c.width);
    EXPECT_EQ(410.0, c.height);
    EXPECT_EQ(std::string("CAMERA 3"), c.name());

    // Traditional set
    c.width.set(640);
    c.height.set(480.0);
    c.name.set(std::string("camera iv"));
    EXPECT_EQ(640, c.width.get());
    EXPECT_EQ(480.0, c.height.get());
    EXPECT_EQ(std::string("camera iv"), c.name());

    // Copy construction
    camera c2(c);
    EXPECT_EQ(640, c2.width());
    EXPECT_EQ(480.0, c2.height());
    EXPECT_EQ(std::string("camera iv"), c2.name());
}

// Test ro_value_scalar_property
class ro_camera
{
public:
    p::ro_value_scalar_property<int> width;
    p::ro_value_scalar_property<double> height;
    p::ro_value_scalar_property<std::string> name;

    ro_camera()
        : width(std::string("width"), 320)
        , height(std::string("height"), 200.0)
        , name(std::string("name"), std::string("camera"))
    {
    }
};

TEST(properties_test_suite, ro_scalar_properties)
{
    ro_camera c;

    // Method oriented get
    EXPECT_EQ(320, c.width());
    EXPECT_EQ(200.0, c.height());
    EXPECT_EQ(std::string("camera"), c.name());

    // Cast operator oriented get
    EXPECT_EQ(320, static_cast<int>(c.width));
    EXPECT_EQ(200.0, static_cast<double>(c.height));
    EXPECT_EQ(std::string("camera"), static_cast<std::string>(c.name));

    // Implicit cast oriented get
    EXPECT_TRUE(320 == c.width);
    EXPECT_TRUE(200.0 == c.height);
    EXPECT_TRUE(std::string("camera") == c.name);

    // Traditional get
    EXPECT_EQ(320, c.width.get());
    EXPECT_EQ(200.0, c.height.get());
    EXPECT_EQ(std::string("camera"), c.name.get());

    // Copy construction
    ro_camera c2(c);
    EXPECT_EQ(320, c2.width());
    EXPECT_EQ(200.0, c2.height());
    EXPECT_EQ(std::string("camera"), c2.name());
}

// Test wo_value_scalar_property
class wo_camera
{
public:
    p::wo_value_scalar_property<int> width;
    p::wo_value_scalar_property<double> height;
    p::wo_value_scalar_property<std::string> name;

    wo_camera()
        : width(std::string("width"), 320)
        , height(std::string("height"), 200.0)
        , name(std::string("name"), std::string("camera"))
    {
    }
};

TEST(properties_test_suite, wo_scalar_properties)
{
    wo_camera c;

    // Method oriented set
    c.width(480);
    c.height(340.0);
    c.name("Camera 2");

    // Assign operator oriented set
    c.width = 560;
    c.height = 410.0;
    c.name = std::string("CAMERA 3");

    // Traditional set
    c.width.set(640);
    c.height.set(480.0);
    c.name.set(std::string("camera iv"));

    // Copy construction
    wo_camera c2(c);
}

// Test ref_scalar_property
class ref_camera
{
public:
    p::ref_scalar_property<int> width;
    p::ref_scalar_property<double> height;
    p::ref_scalar_property<std::string> name;

    ref_camera()
        : width(std::string("width"))
        , height(std::string("height"))
        , name(std::string("name"))
    {
    }
};

TEST(properties_test_suite, ref_scalar_properties)
{
    ref_camera c;

    // Verify default values
    EXPECT_TRUE(c.width.empty() == true);
    EXPECT_TRUE(c.height.empty() == true);
    EXPECT_TRUE(c.name.empty() == true);

    // Method oriented get
    int w1 = 320;
    double h1 = 200.0;
    std::string n1("camera");
    c.width.set(w1);
    c.height.set(h1);
    c.name.set(n1);
    EXPECT_EQ(320, c.width());
    EXPECT_EQ(200.0, c.height());
    EXPECT_EQ(std::string("camera"), c.name());

    // Cast operator oriented get
    EXPECT_EQ(320, static_cast<int>(c.width));
    EXPECT_EQ(200.0, static_cast<double>(c.height));
    EXPECT_EQ(std::string("camera"), static_cast<std::string>(c.name));

    // Implicit cast oriented get
    EXPECT_TRUE(320 == c.width);
    EXPECT_TRUE(200.0 == c.height);
    EXPECT_TRUE(std::string("camera") == c.name);

    // Traditional get
    EXPECT_EQ(320, c.width.get());
    EXPECT_EQ(200.0, c.height.get());
    EXPECT_EQ(std::string("camera"), c.name.get());

    // Method oriented set
    int w2 = 480;
    double h2 = 340.0;
    std::string n2("Camera 2");
    c.width(w2);
    c.height(h2);
    c.name(n2);
    EXPECT_EQ(480, c.width());
    EXPECT_EQ(340.0, c.height());
    EXPECT_EQ(std::string("Camera 2"), c.name());

    // Assign operator oriented set
    int w3 = 560;
    double h3 = 410.0;
    std::string n3("CAMERA 3");
    c.width = w3;
    c.height = h3;
    c.name = n3;
    EXPECT_EQ(560, c.width);
    EXPECT_EQ(410.0, c.height);
    EXPECT_EQ(std::string("CAMERA 3"), c.name());

    // Traditional set
    int w4 = 640;
    double h4 = 480.0;
    std::string n4("camera iv");
    c.width.set(w4);
    c.height.set(h4);
    c.name.set(n4);
    EXPECT_EQ(640, c.width.get());
    EXPECT_EQ(480.0, c.height.get());
    EXPECT_EQ(std::string("camera iv"), c.name());

    // Assign referenced object oriented set
    w4 = 800;
    h4 = 600.0;
    n4 = "CAMERA IV";
    EXPECT_EQ(800, c.width.get());
    EXPECT_EQ(600.0, c.height.get());
    EXPECT_EQ(std::string("CAMERA IV"), c.name());

    // Copy construction
    ref_camera c2(c);
    EXPECT_EQ(800, c2.width());
    EXPECT_EQ(600.0, c2.height());
    EXPECT_EQ(std::string("CAMERA IV"), c2.name());
}

// Test ro_ref_scalar_property
class ro_ref_camera
{
public:
    p::ro_ref_scalar_property<int> width;
    p::ro_ref_scalar_property<double> height;
    p::ro_ref_scalar_property<std::string> name;

    ro_ref_camera()
        : width(std::string("width"), m_width)
        , height(std::string("height"), m_height)
        , name(std::string("name"), m_name)
        , m_width(320)
        , m_height(200.0)
        , m_name(std::string("camera"))
    {
    }

private:
    int m_width;
    double m_height;
    std::string m_name;
};

TEST(properties_test_suite, ro_ref_scalar_properties)
{
    ro_ref_camera c;

    // Verify default values
    EXPECT_TRUE(c.width.empty() == false);
    EXPECT_TRUE(c.height.empty() == false);
    EXPECT_TRUE(c.name.empty() == false);

    // Method oriented get
    EXPECT_EQ(320, c.width());
    EXPECT_EQ(200.0, c.height());
    EXPECT_EQ(std::string("camera"), c.name());

    // Cast operator oriented get
    EXPECT_EQ(320, static_cast<int>(c.width));
    EXPECT_EQ(200.0, static_cast<double>(c.height));
    EXPECT_EQ(std::string("camera"), static_cast<std::string>(c.name));

    // Implicit cast oriented get
    EXPECT_TRUE(320 == c.width);
    EXPECT_TRUE(200.0 == c.height);
    EXPECT_TRUE(std::string("camera") == c.name);

    // Traditional get
    EXPECT_EQ(320, c.width.get());
    EXPECT_EQ(200.0, c.height.get());
    EXPECT_EQ(std::string("camera"), c.name.get());

    // Copy construction
    ro_ref_camera c2(c);
    EXPECT_TRUE(c2.width.empty() == false);
    EXPECT_TRUE(c2.height.empty() == false);
    EXPECT_TRUE(c2.name.empty() == false);
    EXPECT_EQ(320, c2.width());
    EXPECT_EQ(200.0, c2.height());
    EXPECT_EQ(std::string("camera"), c2.name());
}

// Test wo_ref_scalar_property
class wo_ref_camera
{
public:
    p::wo_ref_scalar_property<int> width;
    p::wo_ref_scalar_property<double> height;
    p::wo_ref_scalar_property<std::string> name;

    wo_ref_camera()
        : width(std::string("width"))
        , height(std::string("height"))
        , name(std::string("name"))
    {
    }
};

TEST(properties_test_suite, wo_ref_scalar_properties)
{
    wo_ref_camera c;

    // Verify default values
    EXPECT_TRUE(c.width.empty() == true);
    EXPECT_TRUE(c.height.empty() == true);
    EXPECT_TRUE(c.name.empty() == true);

    // Method oriented set
    int w2 = 480;
    double h2 = 340.0;
    std::string n2("Camera 2");
    c.width(w2);
    c.height(h2);
    c.name(n2);

    // Assign operator oriented set
    int w3 = 560;
    double h3 = 410.0;
    std::string n3("CAMERA 3");
    c.width = w3;
    c.height = h3;
    c.name = n3;

    // Traditional set
    int w4 = 640;
    double h4 = 480.0;
    std::string n4("camera iv");
    c.width.set(w4);
    c.height.set(h4);
    c.name.set(n4);

    // Assign referenced object oriented set
    w4 = 800;
    h4 = 600.0;
    n4 = "CAMERA IV";

    // Copy construction
    wo_ref_camera c2(c);
}

// Test property
class device_driver
{
// Camera driver, not modifyable, provided by third-party
public:
    ~device_driver()
    {
    }

    device_driver()
        : _fps(0)
    {
    }

    void set_target_fps(int fps)
    {
        _fps = fps;
    }

    int get_current_fps() const
    {
        return _fps;
    }

private:
    int _fps;
};

class fps_camera
    : public camera
{
public:
    p::property<int> fps;

    fps_camera()
        : camera()
        , fps(std::string("fps"))
        , _d()
    {
        update_bindings();
    }

    fps_camera(const fps_camera& v)
        : camera(v)
        , fps(v.fps)
        , _d(v._d)
    {
        update_bindings();
    }

    fps_camera& operator=(const fps_camera& v)
    {
        camera::operator=(v);
        fps = v.fps;
        _d = v._d;
        update_bindings();
    }

private:
    void update_bindings()
    {
        fps.getter(std::bind(&device_driver::get_current_fps, &_d));
        fps.setter(std::bind(&device_driver::set_target_fps, &_d, ph::_1));
    }

private:
    device_driver _d;
};

TEST(properties_test_suite, value_properties)
{
    fps_camera c;

    // INHERITED PROPERTIES

    // Method oriented get
    EXPECT_EQ(320, c.width());
    EXPECT_EQ(200.0, c.height());
    EXPECT_EQ(std::string("camera"), c.name());

    // Cast operator oriented get
    EXPECT_EQ(320, static_cast<int>(c.width));
    EXPECT_EQ(200.0, static_cast<double>(c.height));
    EXPECT_EQ(std::string("camera"), static_cast<std::string>(c.name));

    // Implicit cast oriented get
    EXPECT_TRUE(320 == c.width);
    EXPECT_TRUE(200.0 == c.height);
    EXPECT_TRUE(std::string("camera") == c.name);

    // Traditional get
    EXPECT_EQ(320, c.width.get());
    EXPECT_EQ(200.0, c.height.get());
    EXPECT_EQ(std::string("camera"), c.name.get());

    // Method oriented set
    c.width(480);
    c.height(340.0);
    c.name("Camera 2");
    EXPECT_EQ(480, c.width());
    EXPECT_EQ(340.0, c.height());
    EXPECT_EQ(std::string("Camera 2"), c.name());

    // Assign operator oriented set
    c.width = 560;
    c.height = 410.0;
    c.name = std::string("CAMERA 3");
    EXPECT_EQ(560, c.width);
    EXPECT_EQ(410.0, c.height);
    EXPECT_EQ(std::string("CAMERA 3"), c.name());

    // Traditional set
    c.width.set(640);
    c.height.set(480.0);
    c.name.set(std::string("camera iv"));
    EXPECT_EQ(640, c.width.get());
    EXPECT_EQ(480.0, c.height.get());
    EXPECT_EQ(std::string("camera iv"), c.name());

    // Copy construction
    camera c2(c);
    EXPECT_EQ(640, c2.width());
    EXPECT_EQ(480.0, c2.height());
    EXPECT_EQ(std::string("camera iv"), c2.name());

    // PROXY

    c.fps(16);

    // Method oriented get
    EXPECT_EQ(16, c.fps());

    // Cast operator oriented get
    EXPECT_EQ(16, static_cast<int>(c.fps));

    // Implicit cast oriented get
    EXPECT_TRUE(16 == c.fps);

    // Traditional get
    EXPECT_EQ(16, c.fps.get());

    // Method oriented set
    c.fps(24);
    EXPECT_EQ(24, c.fps());

    // Assign operator oriented set
    c.fps = 25;
    EXPECT_EQ(25, c.fps);

    // Traditional set
    c.fps.set(30);
    EXPECT_EQ(30, c.fps.get());

    // Copy construction
    fps_camera c3(c);
    EXPECT_EQ(640, c3.width());
    EXPECT_EQ(480.0, c3.height());
    EXPECT_EQ(std::string("camera iv"), c3.name());
    EXPECT_EQ(30, c3.fps());
}

// Test ro_property
class ro_fps_camera
    : public ro_camera
{
public:
    p::ro_property<int> fps;

    ro_fps_camera()
        : ro_camera()
        , fps(std::string("fps"))
        , _d()
    {
        _d.set_target_fps(16);
        update_bindings();
    }

    ro_fps_camera(const ro_fps_camera& v)
        : ro_camera(v)
        , fps(v.fps)
        , _d(v._d)
    {
        update_bindings();
    }

private:
    void update_bindings()
    {
        fps.getter(std::bind(&device_driver::get_current_fps, &_d));
    }

private:
    device_driver _d;
};

TEST(properties_test_suite, ro_value_properties)
{
    ro_fps_camera c;

    // INHERITED PROPERTIES

    // Method oriented get
    EXPECT_EQ(320, c.width());
    EXPECT_EQ(200.0, c.height());
    EXPECT_EQ(std::string("camera"), c.name());

    // Cast operator oriented get
    EXPECT_EQ(320, static_cast<int>(c.width));
    EXPECT_EQ(200.0, static_cast<double>(c.height));
    EXPECT_EQ(std::string("camera"), static_cast<std::string>(c.name));

    // Implicit cast oriented get
    EXPECT_TRUE(320 == c.width);
    EXPECT_TRUE(200.0 == c.height);
    EXPECT_TRUE(std::string("camera") == c.name);

    // Traditional get
    EXPECT_EQ(320, c.width.get());
    EXPECT_EQ(200.0, c.height.get());
    EXPECT_EQ(std::string("camera"), c.name.get());

    // Copy construction
    ro_camera c2(c);
    EXPECT_EQ(320, c2.width());
    EXPECT_EQ(200.0, c2.height());
    EXPECT_EQ(std::string("camera"), c2.name());

    // PROXY

    // Method oriented get
    EXPECT_EQ(16, c.fps());

    // Cast operator oriented get
    EXPECT_EQ(16, static_cast<int>(c.fps));

    // Implicit cast oriented get
    EXPECT_TRUE(16 == c.fps);

    // Traditional get
    EXPECT_EQ(16, c.fps.get());

    // Copy construction
    ro_fps_camera c3(c);
    EXPECT_EQ(320, c3.width());
    EXPECT_EQ(200.0, c3.height());
    EXPECT_EQ(std::string("camera"), c3.name());
    EXPECT_EQ(16, c3.fps());
}

// Test wo_property
class wo_fps_camera
    : public wo_camera
{
public:
    p::wo_property<int> fps;

    wo_fps_camera()
        : wo_camera()
        , fps(std::string("fps"))
        , _d()
    {
        update_bindings();
    }

    wo_fps_camera(const wo_fps_camera& v)
        : wo_camera(v)
        , fps(v.fps)
        , _d(v._d)
    {
        update_bindings();
    }

private:
    void update_bindings()
    {
        fps.setter(std::bind(&device_driver::set_target_fps, &_d, ph::_1));
    }

private:
    device_driver _d;
};

TEST(properties_test_suite, wo_value_properties)
{
    wo_fps_camera c;

    // INHERITED PROPERTIES

    // Method oriented set
    c.width(480);
    c.height(340.0);
    c.name("Camera 2");

    // Assign operator oriented set
    c.width = 560;
    c.height = 410.0;
    c.name = std::string("CAMERA 3");

    // Traditional set
    c.width.set(640);
    c.height.set(480.0);
    c.name.set(std::string("camera iv"));

    // Copy construction
    wo_camera c2(c);

    // PROXY

    // Method oriented set
    c.fps(24);

    // Assign operator oriented set
    c.fps = 25;

    // Traditional set
    c.fps.set(30);

    // Copy construction
    wo_fps_camera c3(c);
}
