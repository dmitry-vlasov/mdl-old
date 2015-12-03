/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_EntityAnnotation.hpp                 */
/* Description:     functional OWL2 entity annotation source                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_ENTITY_ANNOTATION_HPP_
#define DEL_OWL_FUNC_SOURCE_ENTITY_ANNOTATION_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace source {

class EntityAnnotation :
	public Writable,
	public Scalar<EntityAnnotation> {
public :
	enum Kind {
		CLASS,
		OBJECT_PROPERTY
	};

	EntityAnnotation
	(
		const Location&,
		const Kind,
		const String&,
		const Annotation*
	);
	EntityAnnotation
	(
		const Location&,
		const Kind,
		const String&,
		const String&
	);
	virtual ~ EntityAnnotation();

	Kind getKind() const;
	const String& getName() const;
	const String& getLabel() const;
	const Annotation* getAnnotation() const;
	void setAnnotation (const Annotation*);

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const Kind   kind_;
	const String name_;
	const String label_;
	const Annotation* annotation_;
};

}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_ENTITY_ANNOTATION_HPP_*/
