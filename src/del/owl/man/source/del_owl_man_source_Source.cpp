/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Source.cpp                            */
/* Description:     manchester OWL source source                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_SOURCE_CPP_
#define DEL_OWL_MAN_SOURCE_SOURCE_CPP_

#include "del/owl/del_owl.hpp"

namespace del {
namespace owl {
namespace man {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Source :: Source (const del :: Path& sourcePath, const del :: Path& targetPath) :
	namespaceVector_ (INITIAL_NAMESPACE_VECTOR_CAPACITY),
	annotationsVector_ (INITIAL_ANNOTATIONS_VECTOR_CAPACITY),
	ontologyVector_ (INITIAL_ONTOLOGY_VECTOR_CAPACITY),
	objectPropertyVector_ (INITIAL_OBJECT_PROPERTY_VECTOR_CAPACITY),
	classVector_ (INITIAL_CLASS_VECTOR_CAPACITY),
	sourcePath_ (sourcePath),
	targetPath_ (targetPath),
	output_ (NULL),
	isWritable_ (true) {
	}
	Source :: Source (const del :: Path& sourcePath) :
	namespaceVector_ (INITIAL_NAMESPACE_VECTOR_CAPACITY),
	annotationsVector_ (INITIAL_ANNOTATIONS_VECTOR_CAPACITY),
	ontologyVector_ (INITIAL_ONTOLOGY_VECTOR_CAPACITY),
	objectPropertyVector_ (INITIAL_OBJECT_PROPERTY_VECTOR_CAPACITY),
	classVector_ (INITIAL_CLASS_VECTOR_CAPACITY),
	sourcePath_ (sourcePath),
	targetPath_ (),
	output_ (NULL),
	isWritable_ (false) {
	}
	Source :: ~ Source() {
		deleteAggregateObject (output_);
	}

	const del :: Theory*
	Source :: createTheory() const
	{
		const String& nameString = sourcePath_.getName();
		const value :: Theory
			name = Table :: theories()->add (nameString);
		del :: source :: Theory*
			theory = new del :: source :: Theory (name);
		for (value :: Integer i = 0; i < classVector_.getSize(); ++ i) {
			const Class* const
				clas = classVector_.getValue (i);
			clas->addToTheory (theory);
		}
		return theory;
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
			theory = createTheory();
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

	bool
	Source :: isWritable() const {
		return isWritable_;
	}
	void
	Source :: addNamespace (const Namespace* nspace) {
		namespaceVector_.add (nspace);
	}
	void
	Source :: addOntology (const Ontology* ontology) {
		ontologyVector_.add (ontology);
	}
	void
	Source :: addAnnotations (const Annotations* annotations) {
		annotationsVector_.add (annotations);
	}
	void
	Source :: addObjectProperty (const ObjectProperty* objectProperty) {
		objectPropertyVector_.add (objectProperty);
	}
	void
	Source :: addClass (const Class* clas) {
		classVector_.add (clas);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Source :: translate (String& string) const
	{
		if (Config :: commentStuff()) {
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
		string << endLine;
	}
	void
	Source :: replicate (String& string) const
	{
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
		string << endLine;
		for (value :: Integer i = 0; i < classVector_.getSize(); ++ i) {
			const Class* const
				clas = classVector_.getValue (i);
			string << *clas;
		}
		string << endLine;
	}
	void
	Source :: write() const
	{
		const String& file = targetPath_.getString();
		targetPath_.provideDirectory();
		output_ = new Output (file);
		output_->open();

		output_->buffer() << del :: Token :: theory_ << space;
		output_->buffer() << sourcePath_.getName() << space;
		output_->buffer() << del :: Token :: equality_ << space;
		output_->buffer() << del :: Token :: openBrace_ << endLine;
		for (value :: Integer i = 0; i < classVector_.getSize(); ++ i) {
			const Class* const
				clas = classVector_.getValue (i);
			clas->translate (output_->buffer());
			output_->flush();
		}
		output_->buffer() << del :: Token :: closeBrace_ << endLine;
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
		volume += namespaceVector_.getVolume();
		volume += annotationsVector_.getVolume();
		volume += ontologyVector_.getVolume();
		volume += objectPropertyVector_.getVolume();
		volume += classVector_.getVolume();
		volume += sourcePath_.getVolume();
		volume += targetPath_.getVolume();
		volume += getAggregateVolume (output_);
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

#endif /*DEL_OWL_MAN_SOURCE_SOURCE_CPP_*/
