/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Pair.hpp                                  */
/* Description:     simple pair container                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_PAIR_HPP_
#define NSTD_CONTAINER_PAIR_HPP_

namespace nstd {
namespace container {

template<class T_1, class T_2>
class Pair {
public :
	typedef T_1 Type_1_;
	typedef T_2 Type_2_;

	Pair ();
	Pair (const Type_1_, const Type_2_);
	Pair (const Pair&);
	~ Pair();

	Type_1_ getFirstValue() const;
	Type_2_ getSecondValue() const;
	void setFirstValue (const Type_1_);
	void setSecondValue (const Type_2_);

	void operator = (const Pair&);
	bool operator == (const Pair&) const;
	bool operator != (const Pair&) const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
	Type_1_ value_1_;
	Type_2_ value_2_;
};

}
}

#endif /*NSTD_CONTAINER_PAIR_HPP_*/
