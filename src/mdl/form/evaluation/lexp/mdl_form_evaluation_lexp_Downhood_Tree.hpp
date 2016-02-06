/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Downhood_Tree.hpp               */
/* Description:     a downhood tree of a point in a proof                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

template<class A>
class Downhood<A> :: Tree_ :
	public object :: Object,
	public Scalar<Tree_> {
public :
	typedef
		typename mdl :: vector :: Vector
		<
			Tree_,
			storage :: ByPointer,
			allocator :: Heap
		>
		Down_;

	Tree_ (const mdl :: proof :: Step*, const value :: Integer depth = 0);
	Tree_ (const Node_*, const value :: Integer depth = 0);
	Tree_ (const Tree_*);
	virtual ~ Tree_();

	value :: Real getDistance
	(
		const Tree_*,
		const Factors&,
		const value :: Integer depth = 0
	) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	value :: Real getDistance
	(
		const array :: Expression* expression_1,
		const array :: Expression* expression_2
	) const;

	array :: Expression* expression_;
	Down_ down_;
};

}
}
}
}


