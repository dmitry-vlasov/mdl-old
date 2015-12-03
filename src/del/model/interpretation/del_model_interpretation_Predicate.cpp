/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_Predicate.cpp                   */
/* Description:     set of singletons (predicate) in a model of a theory       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_INTERPRETATION_PREDICATE_CPP_
#define DEL_MODEL_INTERPRETATION_PREDICATE_CPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace interpretation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Predicate<A> :: Predicate (Model* model, const value :: Integer size) :
	model_ (model),
	set_ (size),
	tmpSingleton_ () {
	}
	template<class A>
	inline
	Predicate<A> :: Predicate
	(
		Model* model,
		const Symbol symbol,
		const Node* node,
		const Formula* formula
	) :
	model_ (model),
	set_ (INITIAL_CAPACITY),
	tmpSingleton_ ()
	{
		if (symbol.isDefined()) {
			const Singleton_* singleton = new Singleton_ (model_, symbol, node, formula);
			set_.add (singleton);
		}
	}
	template<class A>
	inline
	Predicate<A> :: Predicate
	(
		Model* model,
		const Symbol symbol,
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) :
	model_ (model),
	set_ (INITIAL_CAPACITY),
	tmpSingleton_ ()
	{
		const Singleton_*
			singleton = new Singleton_
			(
				model_,
				symbol,
				nodes,
				size,
				formula
			);
		set_.add (singleton);
	}
	template<class A>
	template<class A1>
	inline
	Predicate<A> :: Predicate (const Predicate<A1>& singletonSet, Model* model) :
	model_ (model),
	set_ (singletonSet.set_.getSize()),
	tmpSingleton_ ()
	{
		typedef A1 Allocator;
		typedef
			typename Predicate<Allocator> :: Singleton_
			Singleton;
		for (value :: Integer i = 0; i < singletonSet.set_.getSize(); ++ i) {
			const Singleton* oldSingleton = singletonSet.set_.getValue (i);
			const Singleton_* newSingleton = new Singleton_ (*oldSingleton, model);
			set_.add (newSingleton);
		}
	}
	template<class A>
	Predicate<A> :: ~ Predicate() {
	}

	template<class A>
	inline void
	Predicate<A> :: add (const Node* node)
	{
		const Singleton_* singleton = dynamic_cast<const Singleton_*>(node);
		set_.add (singleton);
	}

	// del :: model :: Predicate implementation
	template<class A>
	value :: Integer
	Predicate<A> :: getSize() const {
		return set_.getSize();
	}
	template<class A>
	const Positive*
	Predicate<A> :: getNode (const value :: Integer i) const {
		return set_.getValue (i);
	}
	template<class A>
	const Node*
	Predicate<A> :: find (const Symbol symbol) const
	{
		tmpSingleton_.setSymbol (symbol);
		const value :: Integer index = set_.find (&tmpSingleton_);
		if (index  == value :: undefined :: INTEGER) {
			return NULL;
		} else {
			return set_.getValue (index);
		}
	}
	template<class A>
	bool
	Predicate<A> :: addNode
	(
		const Symbol symbol,
		const Node* node,
		const Formula* formula
	)
	{
		const Node* n = find (symbol);
		if (n == NULL) {
			const Singleton_* newSingleton = new Singleton_ (model_, symbol, node, formula);
			set_.add (newSingleton);
			return true;
		} else {
			const Singleton_* singleton = dynamic_cast<const Singleton_*>(n);
			return singleton->addNode (node, formula);
		}
	}
	template<class A>
	bool
	Predicate<A> :: addNode
	(
		const Symbol symbol,
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	)
	{
		const Node* n = find (symbol);
		if (n == NULL) {
			const Singleton_* newSingleton = new Singleton_ (model_, symbol, nodes, size, formula);
			set_.add (newSingleton);
			return true;
		} else {
			const Singleton_* singleton = dynamic_cast<const Singleton_*>(n);
			return singleton->addNode (nodes, size, formula);
		}
	}
	template<class A>
	model :: Predicate*
	Predicate<A> :: clone (Model* model) const
	{
		Predicate* predicate = new Predicate (model, set_.getSize());
		for (value :: Integer i = 0; i < set_.getSize(); ++ i) {
			const Node* node = set_.getValue (i);
			Node* clone = node->clone (model);
			predicate->add (clone);
		}
		return predicate;
	}
	template<class A>
	bool
	Predicate<A> :: isEqual (const model :: Predicate* predicate, const bool show) const
	{
		if (getSize() != predicate->getSize()) {
			if (show) {
				std :: cout << "Inequality in <interpretation :: Predicate> class." << std :: endl;
				std :: cout << "--------------------------------------------------" << std :: endl;
				std :: cout << "Predicate sizes do not coincide:" << std :: endl;
				std :: cout << " -- size 1 = " << getSize() << std :: endl;
				std :: cout << " -- size 2 = " << predicate->getSize() << std :: endl;
			}
			return false;
		}
		for (value :: Integer i = 0; i < getSize(); ++ i) {
			const Node* node_1 = getNode (i);
			const Singleton_* singleton = dynamic_cast<const Singleton_*>(node_1);
			const Symbol symbol = singleton->getVariable();
			const Node* node_2 = predicate->find (symbol);
			if (node_2 == NULL) {
				if (show) {
					Counter :: show();
					node_2 = predicate->find (symbol);
					std :: cout << "Inequality in <interpretation :: Predicate> class." << std :: endl;
					std :: cout << "--------------------------------------------------" << std :: endl;
					std :: cout << "predicate does not contain a symbol:" << std :: endl;
					std :: cout << " -- symbol = " << symbol << std :: endl;
				}
				return false;
			}
			if (!node_1->isEqual (node_2, show)) {
				return false;
			}
		}
		return true;
	}


using manipulator :: tab;
using manipulator :: endLine;

	// del :: Object interface
	template<class A>
	void
	Predicate<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Predicate<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	Predicate<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += tmpSingleton_.getVolume();
		volume += set_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Predicate<A> :: getSizeOf() const {
		return sizeof (Predicate);
	}
	template<class A>
	void
	Predicate<A> :: show (String& string) const
	{
		Mode mode (string);
		if (mode.getValue (Mode :: SHOW_NODES)) {
			for (value :: Integer i = 0; i < set_.getSize(); ++ i) {
				const Singleton_* singleton = set_.getValue (i);
				string << tab;
				singleton->show (string);
				string << endLine;
			}
		} else {
			for (value :: Integer i = 0; i < set_.getSize(); ++ i) {
				const Singleton_* singleton = set_.getValue (i);
				singleton->show (string);
				if (i + 1 < set_.getSize()) {
					string << ", ";
				}
			}
		}
	}
}
}
}

#endif /*DEL_MODEL_INTERPRETATION_PREDICATE_CPP_*/
