/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_Undefined.hpp                                       */
/* Description:     undefined value template                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {

template<class T>
class Undefined : public type :: undefined :: Type <T> {
};

}


