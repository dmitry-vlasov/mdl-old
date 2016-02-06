/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_storage.hpp                                    */
/* Description:     basic storage policies                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace storage {

	using nstd :: container :: storage :: ByValue;
	using nstd :: container :: storage :: ByPointer;
	using nstd :: container :: storage :: ByInheritance;
}
}


