/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Volume.hpp                                 */
/* Description:     class for program data volume counters                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_VOLUME_HPP_
#define MDL_AUXILIARY_VOLUME_HPP_

#include "mdl/interface/object/mdl_interface_object_Object.hpp"
#include "mdl/mdl.dpp"

namespace mdl {
namespace auxiliary {

class Volume {
public :
	template<class S>
	static void show
	(
		S&,
		bool volume = false,
		bool balance = false,
		bool difference = false,
		bool calculate = true
	);
	static Size_t getBalance();

private :
	struct Data_ {
		Ptrdiff_t source_;
		Ptrdiff_t names_;
		Ptrdiff_t math_;
		Ptrdiff_t prover_;

		Ptrdiff_t object_;
		Ptrdiff_t memory_;
		Ptrdiff_t config_;
		Ptrdiff_t lexer_;
		Ptrdiff_t server_;
		Ptrdiff_t console_;
		Ptrdiff_t parser_;
		Ptrdiff_t refactor_;
		Ptrdiff_t engine_;

		Ptrdiff_t used_;
		Ptrdiff_t allocated_;
		Ptrdiff_t delta_;

		Data_ operator - (Data_);

		void calculateUsed();
		template<class S>
		void show (S&, Ptrdiff_t, const char*);
	};

	static Data_ calculateVolume();
	template<class S>
	static void showVolume (S&, Data_, const char* header);
	template<class S>
	static void showBalance (S&, Data_);

	static Data_ current_;
	static Data_ previous_;
};

}
}

#endif /*MDL_AUXILIARY_VOLUME_HPP_*/
