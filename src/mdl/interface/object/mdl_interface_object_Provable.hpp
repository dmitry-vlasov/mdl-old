/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Provable.hpp                        */
/* Description:     abstract interface for provable objects                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace interface {
namespace object {

class Provable {
public :
	virtual void addProof (Proof*) = 0;

	virtual proof :: Scope* getScope() = 0;
	virtual vector :: Proof& getProofVector() = 0;
	virtual Proof* getProof (const value :: Name name) = 0;

	virtual const proof :: Scope* getScope() const = 0;
	virtual const vector :: Proof& getProofVector() const = 0;
	virtual const Proof* getProof (const value :: Name name) const = 0;
};

}
}
}


