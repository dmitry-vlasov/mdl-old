/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Source.hpp                                 */
/* Description:     abstract interface for del source AST                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Source : public Writable {
public :
	virtual void addAssertion (const Assertion*) = 0;
	virtual void addTheory (const Theory*) = 0;
	virtual void addQuestion (const Question*) = 0;
	virtual void addAnswer (const Answer*) = 0;
	virtual void addSignature (const Signature*) = 0;
	virtual void addComments (const Comments*) = 0;
	virtual void addDecompose (const Decompose*) = 0;
	virtual void addDecomposition (const Decomposition*) = 0;
	virtual void addMinimize (const Minimize*) = 0;
	virtual void addMinimization (const Minimization*) = 0;

	virtual void solve() = 0;
	virtual void decompose() = 0;
	virtual void minimize() = 0;
	virtual void verify() = 0;

	virtual void write() const = 0;

	virtual bool isSolvable() const = 0;
	virtual bool isDecomposable() const = 0;
	virtual bool isMinimizable() const = 0;
	virtual bool isVerifiable() const = 0;
	virtual bool isWritable() const = 0;
};

}
}


