#pragma once

#include <ostream>
#include <iterator>

#include "plotpp/IPlot.hpp"
#include "plotpp/DataRelation.hpp"
#include "plotpp/ArrowHeadStyle.hpp"

namespace plotpp{
	
	template<class Tx1, class Ty1, class Tx2, class Ty2>
	class Arrows : public IPlot{
	public:
		smartest_pointer<Tx1> x1;
		smartest_pointer<Ty1> y1;
		smartest_pointer<Tx2> x2;
		smartest_pointer<Ty2> y2;
		
		DataRelation dataRelation = DataRelation::relative; // relation from [x1, y1] to [x2, y2]
		float lineWidth = 1.5;
		ArrowHeadStyle arrowHeadStyle = ArrowHeadStyle::filled_head;
		
		
		template<typename U1, typename U2, typename U3, typename U4>
		Arrows(U1&& x1, U2&& y1, U3&& x2, U4&& y2, Text title="")
			: IPlot(std::move(title))
			, x1(std::forward<U1>(x1))
			, y1(std::forward<U2>(y1)) 
			, x2(std::forward<U1>(x2))
			, y2(std::forward<U2>(y2)) 
			{}
		
		virtual void print_plot(std::ostream& stream) const {
			if(dataRelation == DataRelation::absolute){
				stream << "using 1:2:(($3)-($1)):($4-$2)";
			}else{
				stream << "using 1:2:3:4";
			}
			
			if(dataRelation == DataRelation::polar){
				stream << " with arrows";
			}else{
				stream << " with vectors";
			}
			
			stream << " " << to_command(arrowHeadStyle);
			stream << " lw " << lineWidth;
			stream << " title '" << this->IPlot::title.str << "'";	
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto x1itr = std::begin(*x1);
			auto y1itr = std::begin(*y1);
			auto x2itr = std::begin(*x2);
			auto y2itr = std::begin(*y2);
			for(; x1itr != std::end(*x1) && y1itr != std::end(*y1) && x2itr != std::end(*x2) && y2itr != std::end(*y2)
				; (void)++x1itr, (void)++y1itr, (void)++x2itr, (void)++y2itr){
				stream << *x1itr << ' ' << *y1itr << ' ' << *x2itr << ' ' << *y2itr << '\n';
			}
		}
	};
	
	/*constructor helper*/
	template<typename U1, typename U2, typename U3, typename U4>
	auto arrows(U1&& x1, U2&& y1, U3&& x2, U4&& y2, Text title="") {
		using Tx1 = std::remove_reference_t<decltype(x1)>;
		using Ty1 = std::remove_reference_t<decltype(y1)>;
		using Tx2 = std::remove_reference_t<decltype(x2)>;
		using Ty2 = std::remove_reference_t<decltype(y2)>;
		return Arrows<Tx1, Ty1, Tx2, Ty2>(
					std::forward<U1>(x1), 
					std::forward<U2>(y1), 
					std::forward<U3>(x2), 
					std::forward<U4>(y2), 
					std::move(title));
	}
	
}