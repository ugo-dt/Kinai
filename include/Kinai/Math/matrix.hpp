#pragma once

# include "type/type.hpp"

namespace Kinai
{

namespace math
{
	template<length_t C, length_t R, typename T>
	struct outerProduct_trait{};

	template<typename T>
	struct outerProduct_trait<2, 2, T>
	{
		typedef mat<2, 2, T> type;
	};

	template<typename T>
	struct outerProduct_trait<2, 3, T>
	{
		typedef mat<3, 2, T> type;
	};

	template<typename T>
	struct outerProduct_trait<2, 4, T>
	{
		typedef mat<4, 2, T> type;
	};

	template<typename T>
	struct outerProduct_trait<3, 2, T>
	{
		typedef mat<2, 3, T> type;
	};

	template<typename T>
	struct outerProduct_trait<3, 3, T>
	{
		typedef mat<3, 3, T> type;
	};

	template<typename T>
	struct outerProduct_trait<3, 4, T>
	{
		typedef mat<4, 3, T> type;
	};

	template<typename T>
	struct outerProduct_trait<4, 2, T>
	{
		typedef mat<2, 4, T> type;
	};

	template<typename T>
	struct outerProduct_trait<4, 3, T>
	{
		typedef mat<3, 4, T> type;
	};

	template<typename T>
	struct outerProduct_trait<4, 4, T>
	{
		typedef mat<4, 4, T> type;
	};

} // math

} // Kinai
