/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_impl_Model.hpp                          */
/* Description:     model of a theory                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"
#include "del/model/del_model.hpp"

namespace del {
namespace model {
namespace queue {
namespace impl {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Model<A> :: Model() :
	queueMap_ (new Map<Allocator_>()),
	predicateMap_ (new PredicateMap<Allocator_>()),
	relationMap_ (new RelationMap<Allocator_>()),
	domainSet_ (INITIAL_DOMAIN_SET_CAPACITY),
	rangeSet_ (INITIAL_RANGE_SET_CAPACITY) {
	}
	template<class A>
	inline
	Model<A> :: Model (const del :: Theory* theory) {
		build (theory);
	}
	template<class A>
	Model<A> :: ~ Model()
	{
		deleteAggregateObject (queueMap_);
		deleteAggregateObject (predicateMap_);
		deleteAggregateObject (relationMap_);
	}

	// queue :: Model implementation
	template<class A>
	void
	Model<A> :: build (const del :: Theory* theory, del :: model :: Model* model)
	{
		// G = toProceedConcepts = N_c;  - множество концептов, глобально требующих обработки
		const del :: Signature* signature = theory->getSignature();
		ConceptSet_ toProceedConcepts;
		for (value :: Integer i = 0; i < signature->getSize(); ++ i) {
			const Symbol& symbol = signature->getSymbol (i);
			if (symbol.isVariable()) {
				toProceedConcepts.add (symbol.getVariable());
			}
		}
		initQueueMap (theory);

		/*
		while (G != 0) {  // цикл, не заканчивается, пока есть хоть один концепт, требующих обработки
			var a \in G;          // берем произвольный концепт,требующий обработки
			var CQ = {a}: P(N_c)  // переменная - множество концептов, локально требующих обработки
			processVicinity (CQ);
			G:=G\CQ; // убираем CQ из глоб. множества тех, которые надо обработать
		}
		 */
		while (!toProceedConcepts.isEmpty()) {
			const value :: Variable a = toProceedConcepts.getFirstValue();
			ConceptSet_ vicinityConcepts;
			vicinityConcepts.add (a);
			processVicinity (vicinityConcepts, model);
			toProceedConcepts.subtract (vicinityConcepts);
		}
	}
	template<class A>
	bool
	Model<A> :: isTrueSubseteq
	(
		const Symbol a,
		const Symbol b
	) const
	{
		return false;
	}

using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;
using manipulator :: endLine;

	// Object implementation
	template<class A>
	void
	Model<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Model<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	Model<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (queueMap_);
		volume += getAggregateVolume (predicateMap_);
		volume += getAggregateVolume (relationMap_);
		volume += domainSet_.getVolume();
		volume += rangeSet_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Model<A> :: getSizeOf() const {
		return sizeof (Model);
	}
	template<class A>
	void
	Model<A> :: show (String& string) const
	{
		string << endLine;
		string << "model" << endLine;
		string << "-----" << endLine;
		string << *predicateMap_ << endLine;
		string << endLine;
		string << *relationMap_ << endLine;
		string << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Model<A> :: initQueueMap (const del :: Theory* theory)
	{
		/*
		Первичная инициализация очередей:
		для каждого концепта a инициализируем
		O(a) =
			{a} u
			{b|a<b\in T} u
			{a_1...a_n->b|a/\a_1/\.../\a_n<b\in T} u
			{Er.b|a<Er.b\in T} u
			{c|T<c\inT};
		O(Er.b) =
			{a |Er.b < a\in T}
		 */

		for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
			const del :: Formula* formula =theory->getFormula (i);
			switch (formula->getKind()) {
			case del :: Formula :: SIMPLE_SUB_KIND : {
				// a ⊑ b, where a and b are primitive terms, then map (a) = b
				initSimpleQueueMap (formula);
				break;
			}
			case del :: Formula :: CONJ_SUB_KIND : {
				// a_1 ⊓ ··· ⊓ a_n ⊑ b, where a_1,...,a_n and b are primitive terms, then
				// map (a) = {a_1...a_n->b|a/\a_1/\.../\a_n<b\in T}
				initConjQueueMap (formula);
				break;
			}
			case del :: Formula :: RIGHT_SUB_KIND : {
				// a ⊑ ∃r.b, where a and b are primitive terms, then map (a) = Er.b
				initRightExistsQueueMap (formula);
				break;
			}
			case del :: Formula :: LEFT_SUB_KIND : {
				// ∃r.a ⊑ b, where a and b are primitive terms, then map (Er.a) = b
				initLeftExistsQueueMap (formula);
				break;
			}
			default :
				break;
			}
		}
	}

	template<class A>
	void
	Model<A> :: initSimpleQueueMap (const del :: Formula* formula)
	{
		// a ⊑ b, where a and b are primitive terms, then map (a) = b
		const value :: Variable a = formula->getTerm (0)->getSymbol().getVariable();
		const value :: Variable b = formula->getTerm (1)->getSymbol().getVariable();
		initConceptQueueMap (formula, a);
		initConceptQueueMap (formula, b);

		queue :: Domain* domain = new domain :: Simple<Allocator_> (formula, a);
		queue :: Range* range = new range :: Simple<Allocator_> (formula, b);

		addDomainRangePair (domain, range);
	}
	template<class A>
	void
	Model<A> :: initConjQueueMap (const del :: Formula* formula)
	{
		// a_1 ⊓ ··· ⊓ a_n ⊑ b, where a_1,...,a_n and b are primitive terms, then
		// map (a) = {a_1...a_n->b|a/\a_1/\.../\a_n<b\in T}
		const del :: Term* leftTerm = formula->getTerm (0);
		const del :: Term* rightTerm = formula->getTerm (1);
		const value :: Integer size = leftTerm->getSize();
		for (value :: Integer k = 0; k < size; ++ k) {
			const value :: Variable a = leftTerm->getSubterm (k)->getSymbol().getVariable();
			const value :: Variable b = rightTerm->getSymbol().getVariable();
			initConceptQueueMap (formula, a);
			initConceptQueueMap (formula, b);
			value :: Variable a_i [size - 1];
			for (value :: Integer i = 0; i < size - 1; ++ i) {
				const value :: Integer
					index = (i < k) ? i : i + 1;
				const value :: Variable
					c_i = leftTerm->getSubterm (index)->getSymbol().getVariable();
				a_i [i] = c_i;
				initConceptQueueMap (formula, c_i);
			}
			queue :: Domain* domain = new domain :: Simple<Allocator_> (formula, a);
			queue :: Range* range = new range :: Conjunction<Allocator_> (formula, a_i, size - 1, b);
			addDomainRangePair (domain, range);
		}
	}
	template<class A>
	void
	Model<A> :: initRightExistsQueueMap (const del :: Formula* formula)
	{
		// a ⊑ ∃r.b, where a and b are primitive terms, then map (a) = Er.b
		const value :: Variable a = formula->getTerm (0)->getSymbol().getVariable();
		const value :: Relation r = formula->getTerm (1)->getSymbol().getRelation();
		const value :: Variable b = formula->getTerm (1)->getSubterm(0)->getSymbol().getVariable();
		initConceptQueueMap (formula, a);
		initConceptQueueMap (formula, b);

		queue :: Domain* domain = new domain :: Simple<Allocator_> (formula, a);
		queue :: Range* range = new range :: Exists<Allocator_> (formula, r, b);

		addDomainRangePair (domain, range);
	}
	template<class A>
	void
	Model<A> :: initLeftExistsQueueMap (const del :: Formula* formula)
	{
		// ∃r.a ⊑ b, where a and b are primitive terms, then map (Er.a) = b
		const value :: Variable a = formula->getTerm (0)->getSubterm(0)->getSymbol().getVariable();
		const value :: Relation r = formula->getTerm (0)->getSymbol().getRelation();
		const value :: Variable b = formula->getTerm (1)->getSymbol().getVariable();
		initConceptQueueMap (formula, a);
		initConceptQueueMap (formula, b);

		queue :: Domain* domain = new domain :: Exists<Allocator_> (formula, r, a);
		queue :: Range* range = new range :: Simple<Allocator_> (formula, b);

		addDomainRangePair (domain, range);
	}
	template<class A>
	void
	Model<A> :: initConceptQueueMap (const del :: Formula* formula, const value :: Variable a)
	{
		// map (a) = a for each concept name a
		queue :: Domain* domain = new domain :: Simple<Allocator_> (formula, a);
		queue :: Range* range = new range :: Simple<Allocator_> (formula, a);

		addDomainRangePair (domain, range);
	}
	template<class A>
	void
	Model<A> :: addDomainRangePair (queue :: Domain* domain, queue :: Range* range)
	{
		value :: Integer domIndex = domainSet_.find (domain);
		if (domIndex != value :: undefined :: INTEGER) {
			domain->commitSuicide();
			domain = domainSet_.getValue (domIndex);
		} else {
			domainSet_.add (domain);
		}
		value :: Integer rangIndex = rangeSet_.find (range);
		if (rangIndex != value :: undefined :: INTEGER) {
			range->commitSuicide();
			range = rangeSet_.getValue (rangIndex);
		} else {
			rangeSet_.add (range);
		}

		set :: Range* rangeSet = queueMap_->map (domain);
		if (!rangeSet->contains (range)) {
			rangeSet->add (range);
		}
	}

	template<class A>
	void
	Model<A> :: processVicinity (ConceptSet_& vicinity, del :: model :: Model* model)
	{
		/*
		boolean proc = true;
		while (proc) {
			proc := false;
			for (b\in CQ) { // перебираем CQ
				for (q\in O(b)) { // перебираем все элементы очереди для b
					proc := proc v process (b, q, CQ);
				}
			}
		}*/

		bool process = true;
		while (process) {
			process = false;
			for (value :: Integer i = 0; i < vicinity.getSize(); ++ i) {
				const value :: Variable b = vicinity.getValue (i);
				set :: Range* rangeSet = queueMap_->map (b);
				for (value :: Integer j = 0; j < rangeSet->getSize(); ++ j) {
					queue :: Range* q = rangeSet->getValue (j);
					const bool result = processQueueElement (b, q, vicinity);
					if (result && model != NULL) {
						q->getFormula()->apply (model);
					}
					process = result || process;
				}
			}
		}
	}
	template<class A>
	bool
	Model<A> :: processQueueElement
	(
		const value :: Variable b,
		queue :: Range* q,
		ConceptSet_& vicinity
	)
	{
		switch (q->getType()) {
		case queue :: Range :: SIMPLE :
			return processSimpleElement (b, q, vicinity);
		case queue :: Range :: CONJ :
			return processConjElement (b, q, vicinity);
		case queue :: Range :: EXISTS :
			return processExistsElement (b, q, vicinity);
		default :
			return false;
		}
	}
	template<class A>
	bool
	Model<A> :: processSimpleElement
	(
		const value :: Variable b,
		queue :: Range* q,
		ConceptSet_& vicinity
	)
	{
		/*
		 if (q == c) {
			O(b):=(O(b) u O(c))\{q};
			if (c\notin S(b)) {
				S(b):=S(b) u S(c);
				retun true;
			} else {
				return false;
			}
		} */
		const value :: Variable c = q->getConcept();
		set :: Range* rangeC = queueMap_->map (c);
		set :: Range* rangeB = queueMap_->map (b);
		rangeB->unite (*rangeC);
		rangeB->removeValue (q);

		queue :: Predicate*
			predicateB = predicateMap_->map (b);

		if (!predicateB->isTrue (c)) {
			queue :: Predicate*
				predicateC = predicateMap_->map (c);
			predicateB->unite (predicateC);
			return true;
		} else {
			return false;
		}
	}
	template<class A>
	bool
	Model<A> :: processConjElement
	(
		const value :: Variable b,
		queue :: Range* q,
		ConceptSet_& vicinity
	)
	{
		/*
		 if (q == a_1,...a_n->c) {
			if (a_1\in S(b) & ... & a_n\in S(b)) {
				O(b):=(O(b) u O(c))\{q};
				S(b):=S(b) u S(c);
				retun true;
			} else {
				return false;
			}
		} */
		const value :: Variable c = q->getConcept();

		queue :: Predicate*
			predicateB = predicateMap_->map (b);
		for (value :: Integer i = 0; i < q->getSize(); ++ i) {
			const value :: Variable a_i = q->getConcept (i);
			if (!predicateB->isTrue (a_i)) {
				return false;
			}
		}
		set :: Range* rangeC = queueMap_->map (c);
		set :: Range* rangeB = queueMap_->map (b);
		rangeB->unite (*rangeC);
		rangeB->removeValue (q);

		queue :: Predicate*
			predicateC = predicateMap_->map (c);
		predicateB->unite (predicateC);
		return true;
	}
	template<class A>
	bool
	Model<A> :: processExistsElement
	(
		const value :: Variable b,
		queue :: Range* q,
		ConceptSet_& vicinity
	)
	{
		/*
		 if (q == Er.c) {
			if ((b,c)\notin R(r)) {

				// b<Er.c i est' term Er.d. Chtoby ego primenit',
				// dolzhno byt' c<d. Togda my vprave sdelat' O(b):=O(b) u O(Er.d).

				R(r):=R(r) u {(b,c)};

				// O(b):=O(b) u U {O(Er.d)|d\in S(c)}

				S(b):=S(b) u U {O(Er.d)|d\in S(c)}
				CQ:=CQ u {c};
				return true;
			} else {
				return false;
			}
		} */
		const value :: Variable c = q->getConcept();
		const value :: Relation r = q->getRelation();
		queue :: Relation* relationR = relationMap_->map (r);
		if (relationR->isTrue (b, c)) {
			return false;
		} else {
			set :: Range* rangeB = queueMap_->map (b);
			relationR->addPair (b, c);
			queue :: Predicate*
				predicateC = predicateMap_->map (c);
			for (value :: Integer i = 0; i < predicateC->getSize(); ++ i) {
				const value :: Variable d = predicateC->getConcept (i);
				set :: Range* rangeExists = queueMap_->map (r, d);
				rangeB->unite (*rangeExists);
			}
			vicinity.add (c);
			return true;
		}
	}
}
}
}
}


