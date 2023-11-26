#include <Request.h>
#include <iostream>
#include <doctest/doctest.h>

TEST_CASE("Test POST Request")
{
	std::string message = "Test Message";
	RequestBuilder requestBuilder;

	httplib::Result res = requestBuilder
		.setMethod("POST")
		.setSchemaDomainPort("http://testurlformencoded.test")
		.AddURLEncodedParam("msg", message)
		.AddURLEncodedParam("msg1", message)
		.AddURLEncodedParam("msg2", message)
		.AddURLEncodedParam("msg3", message)
		.AddOnPreInstantiationCallback([&](RequestBuilder& r) {
			CHECK(r.getSortedURLEncodedParams() == "msg=" + message + "&msg1=" + message + "&msg2=" + message + "&msg3=" + message);
			})
		.Build()
		.Perform();

	CHECK(res);
	CHECK(res->body == message);
}