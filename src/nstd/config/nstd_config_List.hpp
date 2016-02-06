/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_List.hpp                                     */
/* Description:     list of config groups                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "config/nstd_config.dpp"

namespace nstd {
namespace config {

class List {
public :
	List();
	List(const char* groups[], const int count);
	List(const List&);
	~ List();

	bool contains(const char*) const;

	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

protected :
	typedef
		container :: Vector
		<
			const char*,
			container :: storage :: ByValue,
			memory :: allocator :: Standard
		>
		GroupVector_;

	GroupVector_* groupVector_;
	bool hasAllGroup_;
};

}
}


