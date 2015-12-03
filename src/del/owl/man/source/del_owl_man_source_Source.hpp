/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Source.hpp                            */
/* Description:     manchester OWL source source                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_SOURCE_HPP_
#define DEL_OWL_MAN_SOURCE_SOURCE_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace source {

class Source :
	public Writable,
	public Scalar<Source> {
public :
	Source (const del :: Path&);
	Source (const del :: Path&, const del :: Path&);
	virtual ~ Source();

	const del :: Theory* createTheory() const;
	del :: Source* createSource() const;

	bool isWritable() const;
	void addNamespace (const Namespace*);
	void addOntology (const Ontology*);
	void addAnnotations (const Annotations*);
	void addObjectProperty (const ObjectProperty*);
	void addClass (const Class*);

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual void write() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	vector :: Namespace namespaceVector_;
	vector :: Annotations annotationsVector_;
	vector :: Ontology ontologyVector_;
	vector :: ObjectProperty objectPropertyVector_;
	vector :: Class classVector_;
	mutable del :: Path sourcePath_;
	mutable del :: Path targetPath_;
	mutable Output* output_;
	const bool isWritable_;
	enum {
		INITIAL_NAMESPACE_VECTOR_CAPACITY = 8,
		INITIAL_ANNOTATIONS_VECTOR_CAPACITY = 8,
		INITIAL_ONTOLOGY_VECTOR_CAPACITY = 8,
		INITIAL_OBJECT_PROPERTY_VECTOR_CAPACITY = 8,
		INITIAL_CLASS_VECTOR_CAPACITY = 256
	};
};

}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_SOURCE_HPP_*/
