/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_pair.hpp                                       */
/* Description:     basic template for pairs of values                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_PAIR_HPP_
#define DEL_TYPES_PAIR_HPP_

namespace del {
namespace pair {

template<class T, class A = allocator :: Heap>
struct Pair : public Scalar<Pair<T>, A> {
	typedef A Allocator_;
	typedef T Type_;

	Pair();
	Pair (const Type_ first, const Type_ second);
	template<class T1, class A1>
	Pair (const Pair<T1, A1>& pair);
	~ Pair();

	template<class T1, class A1>
	void operator = (const Pair<T1, A1>&);
	template<class T1, class A1>
	bool operator == (const Pair<T1, A1>&) const;
	template<class T1, class A1>
	bool operator != (const Pair<T1, A1>&) const;

	Type_ first_;
	Type_ second_;
};

}
}

#endif /*DEL_TYPES_PAIR_HPP_*/
