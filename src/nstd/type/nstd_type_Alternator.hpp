/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_Alternator.hpp                                 */
/* Description:     type alternator metafunction                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace type {

template<template<class> class N, class A_1, class A_2>
class Alternator<N<A_1>, A_2> {
public :
	typedef N<A_2> Result_;
};

}
}


