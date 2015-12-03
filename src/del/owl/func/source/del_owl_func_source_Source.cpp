/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Source.cpp                           */
/* Description:     functional OWL2 source source                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_SOURCE_CPP_
#define DEL_OWL_FUNC_SOURCE_SOURCE_CPP_

#include "del/owl/del_owl.hpp"

namespace del {
namespace owl {
namespace func {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Source :: Source (const del :: Path& sourcePath, const del :: Path& targetPath) :
	sourcePath_ (sourcePath),
	targetPath_ (targetPath),
	output_ (NULL),
	namespaceVector_ (INITIAL_NAMESPACE_VECTOR_CAPACITY),
	prefixVector_ (INITIAL_PREFIX_VECTOR_CAPACITY),
	unrecognizedVector_(INITIAL_UNERCOGNIZED_VECTOR_CAPACITY),
	ontology_ (NULL) {
	}
	Source :: Source (const del :: Path& sourcePath) :
	sourcePath_ (sourcePath),
	targetPath_ (sourcePath),
	output_ (NULL),
	namespaceVector_ (INITIAL_NAMESPACE_VECTOR_CAPACITY),
	prefixVector_ (INITIAL_PREFIX_VECTOR_CAPACITY),
	unrecognizedVector_(INITIAL_UNERCOGNIZED_VECTOR_CAPACITY),
	ontology_ (NULL)
	{
		switch (Config :: outputFormat()) {
		case Config :: DEL_FORMAT :
			targetPath_.extension() = "del"; break;
		case Config :: MAN_FORMAT :
			targetPath_.extension() = "man"; break;
		case Config :: FUNC_FORMAT :
			targetPath_.extension() = "owl"; break;
		}
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (ontology_);
		deleteAggregateObject (output_);
	}

	const del :: Theory*
	Source :: createTheory() const {
		return ontology_->createTheory();
	}
	del :: Source*
	Source :: createSource() const
	{
		del :: Path* path = NULL;
		if (Config :: getTarget().isUndefined()) {
			path = new del :: Path (sourcePath_);
		} else {
			path = new del :: Path (Config :: getTarget());
		}
		path->extension() = "del";
		del :: source :: Source* source = new del :: source :: Source (*path);
			const del :: Theory*
				theory = ontology_->createTheory();
		if (Config :: getSource().getExtension() != "del") {
			const value :: Integer
				deltaThreshold = Config :: getDeltaThreshold();
			const del :: Signature*
				delta = theory->computeDelta (deltaThreshold);
			const del :: Decompose*
				decompose = new del :: source :: Decompose (theory, delta);

			source->addSignature (delta);
			source->addTheory (theory);
			source->addDecompose (decompose);
		} else {
			source->addTheory (theory);
		}
		delete path;
		return source;
	}
	const Ontology*
	Source :: getOntology() const {
		return ontology_;
	}
	const vector :: Prefix&
	Source :: getPrefixes() const {
		return prefixVector_;
	}

	void
	Source :: addNamespace (const Namespace* namespacee) {
		namespaceVector_.add (namespacee);
	}
	void
	Source :: addPrefix (const Prefix* prefix) {
		prefixVector_.add (prefix);
	}
	void
	Source :: addUnrecognized (const Unrecognized* unrecognized) {
		unrecognizedVector_.add (unrecognized);
	}
	void
	Source :: setOntology (const Ontology* ontology) {
		ontology_ = ontology;
	}
	bool
	Source :: isWritable() const {
		return true;
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Source :: translate (String& string) const
	{
		/*if (Config :: commentStuff()) {
			for (value :: Integer i = 0; i < namespaceVector_.getSize(); ++ i) {
				const Namespace* const
					nspace = namespaceVector_.getValue (i);
				string << *nspace;
			}
			string << endLine;
			for (value :: Integer i = 0; i < annotationsVector_.getSize(); ++ i) {
				const Annotations* const
					annotations = annotationsVector_.getValue (i);
				string << *annotations;
			}
			string << endLine;
			for (value :: Integer i = 0; i < ontologyVector_.getSize(); ++ i) {
				const Ontology* const
					ontology = ontologyVector_.getValue (i);
				string << *ontology;
			}
			string << endLine;
			for (value :: Integer i = 0; i < objectPropertyVector_.getSize(); ++ i) {
				const ObjectProperty* const
					objectProperty = objectPropertyVector_.getValue (i);
				string << *objectProperty;
			}
		}
		string << del :: Token :: theory_ << space;
		string << sourcePath_.getName() << space;
		string << del :: Token :: equality_ << space;
		string << del :: Token :: openBrace_ << endLine;
		for (value :: Integer i = 0; i < classVector_.getSize(); ++ i) {
			const Class* const
				clas = classVector_.getValue (i);
			clas->translate (string);
		}
		string << del :: Token :: closeBrace_ << endLine;
		string << endLine;*/
	}
	void
	Source :: replicate (String& string) const
	{
		for (value :: Integer i = 0; i < namespaceVector_.getSize(); ++ i) {
			const Writable* namespacee = namespaceVector_.getValue (i);
			namespacee->replicate (string);
			string << endLine;
		}
		if (namespaceVector_.getSize() > 0) {
			string << endLine;
		}

		for (value :: Integer i = 0; i < prefixVector_.getSize(); ++ i) {
			const Writable* prefix = prefixVector_.getValue (i);
			prefix->replicate (string);
			string << endLine;
		}
		if (prefixVector_.getSize() > 0) {
			string << endLine;
		}

		for (value :: Integer i = 0; i < unrecognizedVector_.getSize(); ++ i) {
			const Writable* unrecognized = unrecognizedVector_.getValue (i);
			unrecognized->replicate (string);
			string << endLine;
		}
		if (unrecognizedVector_.getSize() > 0) {
			string << endLine;
		}

		ontology_->replicate (string);
		string << endLine;
	}
	void
	Source :: write() const
	{
		const String& file = targetPath_.getString();
		targetPath_.provideDirectory();
		output_ = new Output (file);
		output_->open();
		replicate (output_->buffer());
		output_->buffer() << endLine;
		output_->close();
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
		volume += sourcePath_.getVolume();
		volume += targetPath_.getVolume();
		volume += getAggregateVolume (output_);
		volume += namespaceVector_.getVolume();
		volume += prefixVector_.getVolume();
		volume += unrecognizedVector_.getVolume();
		volume += getAggregateVolume (ontology_);
		return volume;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_SOURCE_CPP_*/
