/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Prefix.hpp                           */
/* Description:     functional OWL2 prefix source                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_PREFIX_HPP_
#define DEL_OWL_FUNC_SOURCE_PREFIX_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace source {

class Prefix :
	public Writable,
	public Scalar<Prefix> {
public :
	Prefix (const String&);
	Prefix (const Location&, const String&);
	virtual ~ Prefix();

	const String& getString() const;
	const Prefix* clone() const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const String string_;
};

}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_PREFIX_HPP_*/
