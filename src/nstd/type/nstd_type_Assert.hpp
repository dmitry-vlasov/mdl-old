/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_Assert.hpp                                     */
/* Description:     compile time assert                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_ASSERT_HPP_
#define NSTD_TYPE_ASSERT_HPP_

namespace nstd {
namespace type {

template<>
class Assert<true> {
};

}
}

#endif /*NSTD_TYPE_ASSERT_HPP_*/
