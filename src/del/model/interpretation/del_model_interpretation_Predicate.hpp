/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_Predicate.hpp                   */
/* Description:     set of concepts (predicate) in a model of a theory       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/model/del_model.dpp"

namespace del {
namespace model {
namespace interpretation {

template<class A>
class Predicate :
	public del :: model :: Predicate,
	public Scalar<Predicate<A>, A> {
public :
	typedef A Allocator_;
	typedef
		typename node :: positive :: Singleton<Allocator_>
		Singleton_;

	Predicate (Model*, const value :: Integer);
	Predicate
	(
		Model*,
		const Symbol = Undefined<Symbol> :: getValue(),
		const Node* = NULL,
		const Formula* = NULL
	);
	Predicate
	(
		Model*,
		const Symbol,
		const Node* [],
		const value :: Integer,
		const Formula* = NULL
	);
	template<class A1>
	Predicate (const Predicate<A1>&, Model*);
	virtual ~ Predicate();

	void add (const Node*);

	// del :: model :: Predicate interface
	virtual value :: Integer getSize() const;
	virtual const Positive* getNode (const value :: Integer) const;
	virtual const Node* find (const Symbol) const;
	virtual bool addNode (const Symbol, const Node* = NULL, const Formula* = NULL);
	virtual bool addNode (const Symbol, const Node* [], const value :: Integer, const Formula*);
	virtual model :: Predicate* clone (Model*) const;
	virtual bool isEqual (const model :: Predicate*, const bool show = false) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Predicate;

	typedef
		del :: set :: Set
		<
			const Singleton_,
			storage :: ByPointer,
			Allocator_
		>
		Predicate_;

	Model* model_;
	Predicate_ set_;
	mutable Singleton_ tmpSingleton_;
	enum {
		INITIAL_CAPACITY = 32,
	};
};

}
}
}


