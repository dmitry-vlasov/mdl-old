/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Source.hpp                           */
/* Description:     functional OWL2 source source                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
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
	const Ontology* getOntology() const;
	const vector :: Prefix& getPrefixes() const;

	void addNamespace (const Namespace*);
	void addPrefix (const Prefix*);
	void addUnrecognized (const Unrecognized*);
	void setOntology (const Ontology*);
	bool isWritable() const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual void write() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	mutable del :: Path sourcePath_;
	mutable del :: Path targetPath_;
	mutable Output* output_;

	enum {
		INITIAL_NAMESPACE_VECTOR_CAPACITY = 32,
		INITIAL_PREFIX_VECTOR_CAPACITY = 32,
		INITIAL_UNERCOGNIZED_VECTOR_CAPACITY = 32
	};

	vector :: Namespace namespaceVector_;
	vector :: Prefix prefixVector_;
	vector :: Unrecognized unrecognizedVector_;
	const Ontology* ontology_;
};

}
}
}
}


