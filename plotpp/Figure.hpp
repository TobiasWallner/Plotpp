#pragma once

#include <memory>
#include <string>
#include <list>
#include <ostream>
#include <iostream>
#include <fstream>

#include "opstream.hpp"

#include "plotpp/TerminalType.hpp"
#include "plotpp/OutputFileType.hpp"
#include "plotpp/Text.hpp"
#include "plotpp/IPlot.hpp"

namespace plotpp{

	class Figure{
	public:
		std::list<std::shared_ptr<IPlot>> plots;
		
		
	public:
		Text title;
		Text xlabel;
		Text ylabel;
		
		float xmin = -1;
		float xmax = +1;
		float ymin = -1;
		float ymax = +1;
		
		bool xautoscale = true;
		bool yautoscale = true;
		
		bool yreverse = false;
		bool xreverse = false;
		
		bool legend = false;
		
		Figure() = default;
		Figure(const Figure&)=delete;
		Figure(Figure&&)=default;
		
		Figure(std::string title_str);
		
		Figure(Text title, Text xlabel, Text ylabel);
		
		/*TODO: Add enable if or requirement that T has to be derived from IPlot*/
		template<class T>
		Figure& add(std::shared_ptr<T>&& plot){
			std::shared_ptr<IPlot> p = std::move(plot);
			this->add(std::move(p));
			return *this;
		}
		
		/*TODO: Add enable if or requirement that T has to be derived from IPlot*/
		template<class T>
		Figure& add(T&& plot){
			using rrT = std::remove_reference_t<T>;
			this->add(std::move(std::make_shared<rrT>(std::forward<rrT>(plot))));
			return *this;
		}
		
		Figure& add(std::shared_ptr<IPlot>&& plot);
		
		void show(OutputFileType filetype) const;
		
		void show(TerminalType TerminalType = TerminalType::NONE) const;
		
		void save(	std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType TerminalType = TerminalType::NONE) const;

		void plot(
			std::ostream& stream, 
			TerminalType TerminalType = TerminalType::NONE,
			std::string saveAs = "") const;
			
		
	};
	
}