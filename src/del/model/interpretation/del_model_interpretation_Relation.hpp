/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_Relation.hpp                    */
/* Description:     interpretation of relation in a model of a theory        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_INTERPRETATION_RELATION_HPP_
#define DEL_MODEL_INTERPRETATION_RELATION_HPP_

#include "del/interface/del_interface.hpp"
#include "del/model/del_model.dpp"

namespace del {
namespace model {
namespace interpretation {

template<class A>
class Relation :
	public del :: model :: Relation,
	public Scalar<Relation<A>, A> {
public :
	typedef A Allocator_;
	typedef
		typename node :: positive :: Pair<Allocator_>
		Pair_;

	Relation (Model*);
	Relation (Model*, const value :: Integer);
	template<class A1>
	Relation (const Relation<A1>&, Model*);
	virtual ~ Relation();

	void add (const Node*);

	// del :: model :: Relation interface
	virtual value :: Integer getSize() const;
	virtual const Positive* getNode (const value :: Integer) const;
	virtual const Node* find (const Symbol, const Symbol) const;
	virtual bool addNode (const Symbol, const Symbol, const Node*, const Formula*);
	virtual model :: Relation* clone (Model*) const;
	virtual bool isEqual (const model :: Relation*, const bool show = false) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Relation;

	typedef
		del :: set :: Set
		<
			const Pair_,
			storage :: ByPointer,
			Allocator_
		>
		Relation_;

	Model* model_;
	Relation_ relation_;
	mutable Pair_ tmpPair_;
	enum {
		INITIAL_CAPACITY = 32,
	};
};

}
}
}

#endif /*DEL_MODEL_INTERPRETATION_RELATION_HPP_*/
