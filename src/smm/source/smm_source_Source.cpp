/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Source.cpp                                    */
/* Description:     smm source                                               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_SOURCE_CPP_
#define SMM_SOURCE_SOURCE_CPP_

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/source/smm_source.hpp"

namespace smm {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Source :: Source () :
	contents_ (new Contents_()) {
	}
	Source :: ~ Source() {
		deleteAggregateObject (contents_);
	}

	// smm :: Source implementation
	void
	Source :: addComponent (const object :: Verifiable* component) {
		contents_->addLast (component);
	}

	// object :: Verifiable implementation
	void
	Source :: verify() const
	{
		const Contents_ :: Node_*
			node = contents_->getFirst();
		while (node != NULL) {
			const object :: Verifiable*
				component = node->getValue();
			//std :: cout << *component;
			component->verify();
			node = node->getNext();
		}
	}

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (contents_);
		return volume;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	void
	Source :: show (String& string) const
	{
		const Contents_ :: Node_*
			node = contents_->getFirst();
		while (node != NULL) {
			const object :: Verifiable*
				component = node->getValue();
			//std :: cout << *component;
			component->show (string);
			node = node->getNext();
		}
		//string << inclusion_->getPath();
	}
}
}

#endif /*SMM_SOURCE_SOURCE_CPP_*/
