/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Unrecognized.hpp                     */
/* Description:     functional OWL2 unrecognized object                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_UNRECOGNIZED_HPP_
#define DEL_OWL_FUNC_SOURCE_UNRECOGNIZED_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace source {

class Unrecognized :
	public Writable,
	public Scalar<Unrecognized> {
public :
	Unrecognized (const String&, const vector :: String&);
	Unrecognized (const Location&, const String&, const vector :: String&);
	virtual ~ Unrecognized();

	const String& getName() const;
	value :: Integer getSize() const;
	const String* getString (const value :: Integer) const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const String name_;
	vector :: String stringVector_;
};

}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_UNRECOGNIZED_HPP_*/
