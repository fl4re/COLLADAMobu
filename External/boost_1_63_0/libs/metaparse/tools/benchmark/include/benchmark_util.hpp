// Copyright Szabolcs Toth (thszabi@gmail.com) 2016.
// Copyright Abel Sinkovics (abel@sinkovics.hu) 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/string.hpp>

template <char C>
struct to_upper_char;

template <> struct to_upper_char<-128> : boost::mpl::char_<95> {};
template <> struct to_upper_char<-127> : boost::mpl::char_<96> {};
template <> struct to_upper_char<-126> : boost::mpl::char_<97> {};
template <> struct to_upper_char<-125> : boost::mpl::char_<98> {};
template <> struct to_upper_char<-124> : boost::mpl::char_<99> {};
template <> struct to_upper_char<-123> : boost::mpl::char_<100> {};
template <> struct to_upper_char<-122> : boost::mpl::char_<101> {};
template <> struct to_upper_char<-121> : boost::mpl::char_<102> {};
template <> struct to_upper_char<-120> : boost::mpl::char_<103> {};
template <> struct to_upper_char<-119> : boost::mpl::char_<104> {};
template <> struct to_upper_char<-118> : boost::mpl::char_<105> {};
template <> struct to_upper_char<-117> : boost::mpl::char_<106> {};
template <> struct to_upper_char<-116> : boost::mpl::char_<107> {};
template <> struct to_upper_char<-115> : boost::mpl::char_<108> {};
template <> struct to_upper_char<-114> : boost::mpl::char_<109> {};
template <> struct to_upper_char<-113> : boost::mpl::char_<110> {};
template <> struct to_upper_char<-112> : boost::mpl::char_<111> {};
template <> struct to_upper_char<-111> : boost::mpl::char_<112> {};
template <> struct to_upper_char<-110> : boost::mpl::char_<113> {};
template <> struct to_upper_char<-109> : boost::mpl::char_<114> {};
template <> struct to_upper_char<-108> : boost::mpl::char_<115> {};
template <> struct to_upper_char<-107> : boost::mpl::char_<116> {};
template <> struct to_upper_char<-106> : boost::mpl::char_<117> {};
template <> struct to_upper_char<-105> : boost::mpl::char_<118> {};
template <> struct to_upper_char<-104> : boost::mpl::char_<119> {};
template <> struct to_upper_char<-103> : boost::mpl::char_<120> {};
template <> struct to_upper_char<-102> : boost::mpl::char_<121> {};
template <> struct to_upper_char<-101> : boost::mpl::char_<122> {};
template <> struct to_upper_char<-100> : boost::mpl::char_<123> {};
template <> struct to_upper_char<-99> : boost::mpl::char_<124> {};
template <> struct to_upper_char<-98> : boost::mpl::char_<125> {};
template <> struct to_upper_char<-97> : boost::mpl::char_<126> {};
template <> struct to_upper_char<-96> : boost::mpl::char_<127> {};
template <> struct to_upper_char<-95> : boost::mpl::char_<-127> {};
template <> struct to_upper_char<-94> : boost::mpl::char_<-126> {};
template <> struct to_upper_char<-93> : boost::mpl::char_<-125> {};
template <> struct to_upper_char<-92> : boost::mpl::char_<-124> {};
template <> struct to_upper_char<-91> : boost::mpl::char_<-123> {};
template <> struct to_upper_char<-90> : boost::mpl::char_<-122> {};
template <> struct to_upper_char<-89> : boost::mpl::char_<-121> {};
template <> struct to_upper_char<-88> : boost::mpl::char_<-120> {};
template <> struct to_upper_char<-87> : boost::mpl::char_<-119> {};
template <> struct to_upper_char<-86> : boost::mpl::char_<-118> {};
template <> struct to_upper_char<-85> : boost::mpl::char_<-117> {};
template <> struct to_upper_char<-84> : boost::mpl::char_<-116> {};
template <> struct to_upper_char<-83> : boost::mpl::char_<-115> {};
template <> struct to_upper_char<-82> : boost::mpl::char_<-114> {};
template <> struct to_upper_char<-81> : boost::mpl::char_<-113> {};
template <> struct to_upper_char<-80> : boost::mpl::char_<-112> {};
template <> struct to_upper_char<-79> : boost::mpl::char_<-111> {};
template <> struct to_upper_char<-78> : boost::mpl::char_<-110> {};
template <> struct to_upper_char<-77> : boost::mpl::char_<-109> {};
template <> struct to_upper_char<-76> : boost::mpl::char_<-108> {};
template <> struct to_upper_char<-75> : boost::mpl::char_<-107> {};
template <> struct to_upper_char<-74> : boost::mpl::char_<-106> {};
template <> struct to_upper_char<-73> : boost::mpl::char_<-105> {};
template <> struct to_upper_char<-72> : boost::mpl::char_<-104> {};
template <> struct to_upper_char<-71> : boost::mpl::char_<-103> {};
template <> struct to_upper_char<-70> : boost::mpl::char_<-102> {};
template <> struct to_upper_char<-69> : boost::mpl::char_<-101> {};
template <> struct to_upper_char<-68> : boost::mpl::char_<-100> {};
template <> struct to_upper_char<-67> : boost::mpl::char_<-99> {};
template <> struct to_upper_char<-66> : boost::mpl::char_<-98> {};
template <> struct to_upper_char<-65> : boost::mpl::char_<-97> {};
template <> struct to_upper_char<-64> : boost::mpl::char_<-96> {};
template <> struct to_upper_char<-63> : boost::mpl::char_<-95> {};
template <> struct to_upper_char<-62> : boost::mpl::char_<-94> {};
template <> struct to_upper_char<-61> : boost::mpl::char_<-93> {};
template <> struct to_upper_char<-60> : boost::mpl::char_<-92> {};
template <> struct to_upper_char<-59> : boost::mpl::char_<-91> {};
template <> struct to_upper_char<-58> : boost::mpl::char_<-90> {};
template <> struct to_upper_char<-57> : boost::mpl::char_<-89> {};
template <> struct to_upper_char<-56> : boost::mpl::char_<-88> {};
template <> struct to_upper_char<-55> : boost::mpl::char_<-87> {};
template <> struct to_upper_char<-54> : boost::mpl::char_<-86> {};
template <> struct to_upper_char<-53> : boost::mpl::char_<-85> {};
template <> struct to_upper_char<-52> : boost::mpl::char_<-84> {};
template <> struct to_upper_char<-51> : boost::mpl::char_<-83> {};
template <> struct to_upper_char<-50> : boost::mpl::char_<-82> {};
template <> struct to_upper_char<-49> : boost::mpl::char_<-81> {};
template <> struct to_upper_char<-48> : boost::mpl::char_<-80> {};
template <> struct to_upper_char<-47> : boost::mpl::char_<-79> {};
template <> struct to_upper_char<-46> : boost::mpl::char_<-78> {};
template <> struct to_upper_char<-45> : boost::mpl::char_<-77> {};
template <> struct to_upper_char<-44> : boost::mpl::char_<-76> {};
template <> struct to_upper_char<-43> : boost::mpl::char_<-75> {};
template <> struct to_upper_char<-42> : boost::mpl::char_<-74> {};
template <> struct to_upper_char<-41> : boost::mpl::char_<-73> {};
template <> struct to_upper_char<-40> : boost::mpl::char_<-72> {};
template <> struct to_upper_char<-39> : boost::mpl::char_<-71> {};
template <> struct to_upper_char<-38> : boost::mpl::char_<-70> {};
template <> struct to_upper_char<-37> : boost::mpl::char_<-69> {};
template <> struct to_upper_char<-36> : boost::mpl::char_<-68> {};
template <> struct to_upper_char<-35> : boost::mpl::char_<-67> {};
template <> struct to_upper_char<-34> : boost::mpl::char_<-66> {};
template <> struct to_upper_char<-33> : boost::mpl::char_<-65> {};
template <> struct to_upper_char<-32> : boost::mpl::char_<-64> {};
template <> struct to_upper_char<-31> : boost::mpl::char_<-63> {};
template <> struct to_upper_char<-30> : boost::mpl::char_<-62> {};
template <> struct to_upper_char<-29> : boost::mpl::char_<-61> {};
template <> struct to_upper_char<-28> : boost::mpl::char_<-60> {};
template <> struct to_upper_char<-27> : boost::mpl::char_<-59> {};
template <> struct to_upper_char<-26> : boost::mpl::char_<-58> {};
template <> struct to_upper_char<-25> : boost::mpl::char_<-57> {};
template <> struct to_upper_char<-24> : boost::mpl::char_<-56> {};
template <> struct to_upper_char<-23> : boost::mpl::char_<-55> {};
template <> struct to_upper_char<-22> : boost::mpl::char_<-54> {};
template <> struct to_upper_char<-21> : boost::mpl::char_<-53> {};
template <> struct to_upper_char<-20> : boost::mpl::char_<-52> {};
template <> struct to_upper_char<-19> : boost::mpl::char_<-51> {};
template <> struct to_upper_char<-18> : boost::mpl::char_<-50> {};
template <> struct to_upper_char<-17> : boost::mpl::char_<-49> {};
template <> struct to_upper_char<-16> : boost::mpl::char_<-48> {};
template <> struct to_upper_char<-15> : boost::mpl::char_<-47> {};
template <> struct to_upper_char<-14> : boost::mpl::char_<-46> {};
template <> struct to_upper_char<-13> : boost::mpl::char_<-45> {};
template <> struct to_upper_char<-12> : boost::mpl::char_<-44> {};
template <> struct to_upper_char<-11> : boost::mpl::char_<-43> {};
template <> struct to_upper_char<-10> : boost::mpl::char_<-42> {};
template <> struct to_upper_char<-9> : boost::mpl::char_<-41> {};
template <> struct to_upper_char<-8> : boost::mpl::char_<-40> {};
template <> struct to_upper_char<-7> : boost::mpl::char_<-39> {};
template <> struct to_upper_char<-6> : boost::mpl::char_<-38> {};
template <> struct to_upper_char<-5> : boost::mpl::char_<-37> {};
template <> struct to_upper_char<-4> : boost::mpl::char_<-36> {};
template <> struct to_upper_char<-3> : boost::mpl::char_<-35> {};
template <> struct to_upper_char<-2> : boost::mpl::char_<-34> {};
template <> struct to_upper_char<-1> : boost::mpl::char_<-33> {};
template <> struct to_upper_char<0> : boost::mpl::char_<-32> {};
template <> struct to_upper_char<1> : boost::mpl::char_<-31> {};
template <> struct to_upper_char<2> : boost::mpl::char_<-30> {};
template <> struct to_upper_char<3> : boost::mpl::char_<-29> {};
template <> struct to_upper_char<4> : boost::mpl::char_<-28> {};
template <> struct to_upper_char<5> : boost::mpl::char_<-27> {};
template <> struct to_upper_char<6> : boost::mpl::char_<-26> {};
template <> struct to_upper_char<7> : boost::mpl::char_<-25> {};
template <> struct to_upper_char<8> : boost::mpl::char_<-24> {};
template <> struct to_upper_char<9> : boost::mpl::char_<-23> {};
template <> struct to_upper_char<10> : boost::mpl::char_<-22> {};
template <> struct to_upper_char<11> : boost::mpl::char_<-21> {};
template <> struct to_upper_char<12> : boost::mpl::char_<-20> {};
template <> struct to_upper_char<13> : boost::mpl::char_<-19> {};
template <> struct to_upper_char<14> : boost::mpl::char_<-18> {};
template <> struct to_upper_char<15> : boost::mpl::char_<-17> {};
template <> struct to_upper_char<16> : boost::mpl::char_<-16> {};
template <> struct to_upper_char<17> : boost::mpl::char_<-15> {};
template <> struct to_upper_char<18> : boost::mpl::char_<-14> {};
template <> struct to_upper_char<19> : boost::mpl::char_<-13> {};
template <> struct to_upper_char<20> : boost::mpl::char_<-12> {};
template <> struct to_upper_char<21> : boost::mpl::char_<-11> {};
template <> struct to_upper_char<22> : boost::mpl::char_<-10> {};
template <> struct to_upper_char<23> : boost::mpl::char_<-9> {};
template <> struct to_upper_char<24> : boost::mpl::char_<-8> {};
template <> struct to_upper_char<25> : boost::mpl::char_<-7> {};
template <> struct to_upper_char<26> : boost::mpl::char_<-6> {};
template <> struct to_upper_char<27> : boost::mpl::char_<-5> {};
template <> struct to_upper_char<28> : boost::mpl::char_<-4> {};
template <> struct to_upper_char<29> : boost::mpl::char_<-3> {};
template <> struct to_upper_char<30> : boost::mpl::char_<-2> {};
template <> struct to_upper_char<31> : boost::mpl::char_<-1> {};
template <> struct to_upper_char<32> : boost::mpl::char_<0> {};
template <> struct to_upper_char<33> : boost::mpl::char_<1> {};
template <> struct to_upper_char<34> : boost::mpl::char_<2> {};
template <> struct to_upper_char<35> : boost::mpl::char_<3> {};
template <> struct to_upper_char<36> : boost::mpl::char_<4> {};
template <> struct to_upper_char<37> : boost::mpl::char_<5> {};
template <> struct to_upper_char<38> : boost::mpl::char_<6> {};
template <> struct to_upper_char<39> : boost::mpl::char_<7> {};
template <> struct to_upper_char<40> : boost::mpl::char_<8> {};
template <> struct to_upper_char<41> : boost::mpl::char_<9> {};
template <> struct to_upper_char<42> : boost::mpl::char_<10> {};
template <> struct to_upper_char<43> : boost::mpl::char_<11> {};
template <> struct to_upper_char<44> : boost::mpl::char_<12> {};
template <> struct to_upper_char<45> : boost::mpl::char_<13> {};
template <> struct to_upper_char<46> : boost::mpl::char_<14> {};
template <> struct to_upper_char<47> : boost::mpl::char_<15> {};
template <> struct to_upper_char<48> : boost::mpl::char_<16> {};
template <> struct to_upper_char<49> : boost::mpl::char_<17> {};
template <> struct to_upper_char<50> : boost::mpl::char_<18> {};
template <> struct to_upper_char<51> : boost::mpl::char_<19> {};
template <> struct to_upper_char<52> : boost::mpl::char_<20> {};
template <> struct to_upper_char<53> : boost::mpl::char_<21> {};
template <> struct to_upper_char<54> : boost::mpl::char_<22> {};
template <> struct to_upper_char<55> : boost::mpl::char_<23> {};
template <> struct to_upper_char<56> : boost::mpl::char_<24> {};
template <> struct to_upper_char<57> : boost::mpl::char_<25> {};
template <> struct to_upper_char<58> : boost::mpl::char_<26> {};
template <> struct to_upper_char<59> : boost::mpl::char_<27> {};
template <> struct to_upper_char<60> : boost::mpl::char_<28> {};
template <> struct to_upper_char<61> : boost::mpl::char_<29> {};
template <> struct to_upper_char<62> : boost::mpl::char_<30> {};
template <> struct to_upper_char<63> : boost::mpl::char_<31> {};
template <> struct to_upper_char<64> : boost::mpl::char_<32> {};
template <> struct to_upper_char<65> : boost::mpl::char_<33> {};
template <> struct to_upper_char<66> : boost::mpl::char_<34> {};
template <> struct to_upper_char<67> : boost::mpl::char_<35> {};
template <> struct to_upper_char<68> : boost::mpl::char_<36> {};
template <> struct to_upper_char<69> : boost::mpl::char_<37> {};
template <> struct to_upper_char<70> : boost::mpl::char_<38> {};
template <> struct to_upper_char<71> : boost::mpl::char_<39> {};
template <> struct to_upper_char<72> : boost::mpl::char_<40> {};
template <> struct to_upper_char<73> : boost::mpl::char_<41> {};
template <> struct to_upper_char<74> : boost::mpl::char_<42> {};
template <> struct to_upper_char<75> : boost::mpl::char_<43> {};
template <> struct to_upper_char<76> : boost::mpl::char_<44> {};
template <> struct to_upper_char<77> : boost::mpl::char_<45> {};
template <> struct to_upper_char<78> : boost::mpl::char_<46> {};
template <> struct to_upper_char<79> : boost::mpl::char_<47> {};
template <> struct to_upper_char<80> : boost::mpl::char_<48> {};
template <> struct to_upper_char<81> : boost::mpl::char_<49> {};
template <> struct to_upper_char<82> : boost::mpl::char_<50> {};
template <> struct to_upper_char<83> : boost::mpl::char_<51> {};
template <> struct to_upper_char<84> : boost::mpl::char_<52> {};
template <> struct to_upper_char<85> : boost::mpl::char_<53> {};
template <> struct to_upper_char<86> : boost::mpl::char_<54> {};
template <> struct to_upper_char<87> : boost::mpl::char_<55> {};
template <> struct to_upper_char<88> : boost::mpl::char_<56> {};
template <> struct to_upper_char<89> : boost::mpl::char_<57> {};
template <> struct to_upper_char<90> : boost::mpl::char_<58> {};
template <> struct to_upper_char<91> : boost::mpl::char_<59> {};
template <> struct to_upper_char<92> : boost::mpl::char_<60> {};
template <> struct to_upper_char<93> : boost::mpl::char_<61> {};
template <> struct to_upper_char<94> : boost::mpl::char_<62> {};
template <> struct to_upper_char<95> : boost::mpl::char_<63> {};
template <> struct to_upper_char<96> : boost::mpl::char_<64> {};
template <> struct to_upper_char<97> : boost::mpl::char_<65> {};
template <> struct to_upper_char<98> : boost::mpl::char_<66> {};
template <> struct to_upper_char<99> : boost::mpl::char_<67> {};
template <> struct to_upper_char<100> : boost::mpl::char_<68> {};
template <> struct to_upper_char<101> : boost::mpl::char_<69> {};
template <> struct to_upper_char<102> : boost::mpl::char_<70> {};
template <> struct to_upper_char<103> : boost::mpl::char_<71> {};
template <> struct to_upper_char<104> : boost::mpl::char_<72> {};
template <> struct to_upper_char<105> : boost::mpl::char_<73> {};
template <> struct to_upper_char<106> : boost::mpl::char_<74> {};
template <> struct to_upper_char<107> : boost::mpl::char_<75> {};
template <> struct to_upper_char<108> : boost::mpl::char_<76> {};
template <> struct to_upper_char<109> : boost::mpl::char_<77> {};
template <> struct to_upper_char<110> : boost::mpl::char_<78> {};
template <> struct to_upper_char<111> : boost::mpl::char_<79> {};
template <> struct to_upper_char<112> : boost::mpl::char_<80> {};
template <> struct to_upper_char<113> : boost::mpl::char_<81> {};
template <> struct to_upper_char<114> : boost::mpl::char_<82> {};
template <> struct to_upper_char<115> : boost::mpl::char_<83> {};
template <> struct to_upper_char<116> : boost::mpl::char_<84> {};
template <> struct to_upper_char<117> : boost::mpl::char_<85> {};
template <> struct to_upper_char<118> : boost::mpl::char_<86> {};
template <> struct to_upper_char<119> : boost::mpl::char_<87> {};
template <> struct to_upper_char<120> : boost::mpl::char_<88> {};
template <> struct to_upper_char<121> : boost::mpl::char_<89> {};
template <> struct to_upper_char<122> : boost::mpl::char_<90> {};
template <> struct to_upper_char<123> : boost::mpl::char_<91> {};
template <> struct to_upper_char<124> : boost::mpl::char_<92> {};
template <> struct to_upper_char<125> : boost::mpl::char_<93> {};
template <> struct to_upper_char<126> : boost::mpl::char_<94> {};
template <> struct to_upper_char<127> : boost::mpl::char_<95> {};

template <class S>
struct to_upper;

template <char... Cs>
struct to_upper<boost::metaparse::string<Cs...>> :
  boost::metaparse::string<to_upper_char<Cs>::value...>
{};

#define CAT_IMPL(a, b) a ## b
#define CAT(a, b) CAT_IMPL(a, b)

#define TEST_STRING(...) to_upper< __VA_ARGS__ >::type CAT(v, __LINE__);
