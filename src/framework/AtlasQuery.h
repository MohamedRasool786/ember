/*
 Copyright (C) 2018 Erik Ogenvik

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef EMBER_ATLASQUERY_H
#define EMBER_ATLASQUERY_H

#include <Atlas/Message/Element.h>

#include <string>
#include <functional>

namespace Ember {

/**
 * Provides utility methods for quickly finding
 */
class AtlasQuery {

public:
	template <typename T>
	static void find(const Atlas::Message::Element& element, const std::string& name, const std::function<void(const T&)>& callback);
	template <typename T>
	static void find(const Atlas::Message::MapType& map, const std::string& name, const std::function<void(const T&)>& callback);
};

template <typename T>
void AtlasQuery::find(const Atlas::Message::Element& element, const std::string& name, const std::function<void(const T&)>& callback) {
	if (element.isMap()) {
		find(element.Map(), name, callback);
	}
}

template <>
void AtlasQuery::find(const Atlas::Message::MapType& map, const std::string& name, const std::function<void(const Atlas::Message::MapType&)>& callback) {
	auto I = map.find(name);
	if (I != map.end()) {
		if (I->second.isMap()) {
			callback(I->second.Map());
		}
	}
}

template <>
void AtlasQuery::find(const Atlas::Message::MapType& map, const std::string& name, const std::function<void(const Atlas::Message::ListType&)>& callback) {
	auto I = map.find(name);
	if (I != map.end()) {
		if (I->second.isList()) {
			callback(I->second.List());
		}
	}
}

template <>
void AtlasQuery::find(const Atlas::Message::MapType& map, const std::string& name, const std::function<void(const Atlas::Message::IntType&)>& callback) {
	auto I = map.find(name);
	if (I != map.end()) {
		if (I->second.isInt()) {
			callback(I->second.Int());
		}
	}
}

template <>
void AtlasQuery::find(const Atlas::Message::MapType& map, const std::string& name, const std::function<void(const Atlas::Message::StringType&)>& callback) {
	auto I = map.find(name);
	if (I != map.end()) {
		if (I->second.isString()) {
			callback(I->second.String());
		}
	}
}

template <>
void AtlasQuery::find(const Atlas::Message::MapType& map, const std::string& name, const std::function<void(const Atlas::Message::FloatType&)>& callback) {
	auto I = map.find(name);
	if (I != map.end()) {
		if (I->second.isFloat()) {
			callback(I->second.Float());
		}
	}
}
}


#endif //EMBER_ATLASQUERY_H