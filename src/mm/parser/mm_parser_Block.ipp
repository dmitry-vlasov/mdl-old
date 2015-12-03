/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_Block.ipp                                      */
/* Description:     metamath block parser                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_IPP_
#define MM_PARSER_BLOCK_IPP_

namespace mm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline const String&
	Block :: getLabel() const {
		return label_;
	}
}
}

#endif /*MM_PARSER_BLOCK_IPP_*/
