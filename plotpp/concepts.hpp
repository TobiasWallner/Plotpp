#pragma once
#include <type_traits>
namespace plotpp{

	template <typename T>
	concept MatrixLike = requires(T&& t, size_t i, size_t j) {
		{ t.rows() } -> std::convertible_to<int>;
		{ t.columns() } -> std::convertible_to<int>;
		{ t.at(i, j) };
	};

	template <typename T>
	concept ForwardIterator = requires(T&& t) {
		{ *t };
		{ ++t } -> std::same_as<T&>;
	};

	template<typename T>
	concept ForwardRange = requires(T&& t){
		{ std::begin(t) } -> ForwardIterator<>;
		{ std::end(t) } -> ForwardIterator<>;
	};

}