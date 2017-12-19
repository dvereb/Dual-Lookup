#include "catch.hpp"

#include "DualLookup.h"

#include <string>

TEST_CASE("all tests", "all") {
	DualLookup<int> container;
	DualLookup<std::string> string_container;

	SECTION ("allow add") {
		REQUIRE(container.add(1, 2));
		REQUIRE(string_container.add("1", "2"));

		// context with same VALUE
		REQUIRE(container.add(1, 3, "a"));
		REQUIRE(string_container.add("1", "3", "a"));

		// context with save EQUIVALENT
		REQUIRE(container.add(3, 2, "b"));
		REQUIRE(string_container.add("3", "2", "b"));

		SECTION ("no duplicates") {
			REQUIRE_FALSE(container.add(1, 2));
			REQUIRE_FALSE(container.add(2, 1));
			REQUIRE_FALSE(container.add(1, 3));
			REQUIRE_FALSE(container.add(2, 3));
			REQUIRE_FALSE(container.add(3, 1));
			REQUIRE_FALSE(container.add(3, 2));
			REQUIRE_FALSE(string_container.add("1", "2"));
			REQUIRE_FALSE(string_container.add("2", "1"));
			REQUIRE_FALSE(string_container.add("1", "3"));
			REQUIRE_FALSE(string_container.add("2", "3"));
			REQUIRE_FALSE(string_container.add("3", "1"));
			REQUIRE_FALSE(string_container.add("3", "2"));

			// context with same VALUE
			REQUIRE_FALSE(container.add(1, 3, "a"));
			REQUIRE_FALSE(container.add(3, 1, "a"));
			REQUIRE_FALSE(container.add(1, 4, "a"));
			REQUIRE_FALSE(container.add(3, 4, "a"));
			REQUIRE_FALSE(container.add(4, 1, "a"));
			REQUIRE_FALSE(container.add(4, 3, "a"));
			REQUIRE_FALSE(string_container.add("1", "3", "a"));
			REQUIRE_FALSE(string_container.add("3", "1", "a"));
			REQUIRE_FALSE(string_container.add("1", "4", "a"));
			REQUIRE_FALSE(string_container.add("3", "4", "a"));
			REQUIRE_FALSE(string_container.add("4", "1", "a"));
			REQUIRE_FALSE(string_container.add("4", "3", "a"));

			// context with save EQUIVALENT
			REQUIRE_FALSE(container.add(3, 2, "b"));
			REQUIRE_FALSE(container.add(2, 3, "b"));
			REQUIRE_FALSE(container.add(3, 4, "b"));
			REQUIRE_FALSE(container.add(2, 4, "b"));
			REQUIRE_FALSE(container.add(4, 3, "b"));
			REQUIRE_FALSE(container.add(4, 2, "b"));
			REQUIRE_FALSE(string_container.add("3", "2", "b"));
			REQUIRE_FALSE(string_container.add("2", "3", "b"));
			REQUIRE_FALSE(string_container.add("3", "4", "b"));
			REQUIRE_FALSE(string_container.add("2", "4", "b"));
			REQUIRE_FALSE(string_container.add("4", "3", "b"));
			REQUIRE_FALSE(string_container.add("4", "2", "b"));
		}

		SECTION ("searches") {
			bool        rtn;
			int         container_result;
			std::string string_container_result;

			SECTION ("found and not found") {
				REQUIRE(container.contains(1));
				REQUIRE(string_container.contains("1"));
				REQUIRE_FALSE(container.contains(10));
				REQUIRE_FALSE(string_container.contains("10"));

				// context with same VALUE
				REQUIRE(container.contains(1, "a"));
				REQUIRE(string_container.contains("1", "a"));
				REQUIRE_FALSE(container.contains(10, "a"));
				REQUIRE_FALSE(string_container.contains("10", "a"));

				// context with save EQUIVALENT
				REQUIRE(container.contains(2, "b"));
				REQUIRE(string_container.contains("2", "b"));
				REQUIRE_FALSE(container.contains(10, "b"));
				REQUIRE_FALSE(string_container.contains("10", "b"));
			}

			SECTION ("not found in container and unedited") {
				container_result = 10;
				string_container_result = "10";
				REQUIRE_FALSE(container.get(20, container_result));
				REQUIRE(container_result == 10);
				REQUIRE_FALSE(string_container.get("20", string_container_result));
				REQUIRE(string_container_result == "10");

				// context with same VALUE
				container_result = 10;
				string_container_result = "10";
				REQUIRE_FALSE(container.get(2, container_result, "a"));
				REQUIRE(container_result == 10);
				REQUIRE_FALSE(string_container.get("2", string_container_result, "a"));
				REQUIRE(string_container_result == "10");

				// context with save EQUIVALENT
				container_result = 10;
				string_container_result = "10";
				REQUIRE_FALSE(container.get(1, container_result, "b"));
				REQUIRE(container_result == 10);
				REQUIRE_FALSE(string_container.get("1", string_container_result, "b"));
				REQUIRE(string_container_result == "10");
			}

			SECTION ("in container and set") {
				container_result = 0;
				REQUIRE(container.get(1, container_result));
				REQUIRE(container_result == 2);
				container_result = 0;
				REQUIRE(container.get(2, container_result));
				REQUIRE(container_result == 1);
				string_container_result = "0";
				REQUIRE(string_container.get("1", string_container_result));
				REQUIRE(string_container_result == "2");
				string_container_result = "0";
				REQUIRE(string_container.get("2", string_container_result));
				REQUIRE(string_container_result == "1");

				// context with same VALUE
				container_result = 0;
				REQUIRE(container.get(1, container_result, "a"));
				REQUIRE(container_result == 3);
				container_result = 0;
				REQUIRE(container.get(3, container_result, "a"));
				REQUIRE(container_result == 1);
				string_container_result = "0";
				REQUIRE(string_container.get("1", string_container_result, "a"));
				REQUIRE(string_container_result == "3");
				string_container_result = "0";
				REQUIRE(string_container.get("3", string_container_result, "a"));
				REQUIRE(string_container_result == "1");

				// context with save EQUIVALENT
				container_result = 0;
				REQUIRE(container.get(3, container_result, "b"));
				REQUIRE(container_result == 2);
				container_result = 0;
				REQUIRE(container.get(2, container_result, "b"));
				REQUIRE(container_result == 3);
				string_container_result = "0";
				REQUIRE(string_container.get("3", string_container_result, "b"));
				REQUIRE(string_container_result == "2");
				string_container_result = "0";
				REQUIRE(string_container.get("2", string_container_result, "b"));
				REQUIRE(string_container_result == "3");
			}
		}

		SECTION ("choosing result side") {
			int container_result;
			container.add(1, 2);

			container_result = 0;
			REQUIRE(container.get(1, container_result));
			CHECK(container_result == 2);
			container_result = 0;
			REQUIRE(container.get(1, container_result, "", DualLookupBase::Type::OPPOSITE));
			CHECK(container_result == 2);
			container_result = 0;
			REQUIRE(container.get(1, container_result, "", DualLookupBase::Type::EQUIVALENT));
			CHECK(container_result == 2);
			container_result = 0;
			REQUIRE(container.get(1, container_result, "", DualLookupBase::Type::VALUE));
			CHECK(container_result == 1);

			container_result = 0;
			REQUIRE(container.get(2, container_result));
			CHECK(container_result == 1);
			container_result = 0;
			REQUIRE(container.get(2, container_result, "", DualLookup<int>::Type::OPPOSITE));
			CHECK(container_result == 1);
			container_result = 0;
			REQUIRE(container.get(2, container_result, "", DualLookup<int>::Type::EQUIVALENT));
			CHECK(container_result == 2);
			container_result = 0;
			REQUIRE(container.get(2, container_result, "", DualLookup<int>::Type::VALUE));
			CHECK(container_result == 1);
			// context with same VALUE
			// context with save EQUIVALENT
		}
	}
}
