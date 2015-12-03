/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Path.hpp                              */
/* Description:     config option for path                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_OPTION_PATH_HPP_
#define NSTD_CONFIG_OPTION_PATH_HPP_

#include "nstd/config/option/nstd_config_option_Option.hpp"
#include "nstd/misc/nstd_misc_Path.hpp"

namespace nstd {
namespace config {
namespace option {

class Path : public Option<nstd :: Path<> > {
public :
	typedef Option<nstd :: Path<> > Option_;
	typedef nstd :: Path<> Path_;

	Path();
	Path
	(
		const char*  cmdString,
		const char*  usageMessage,
		const char   cmdChar = chars :: NULL_CHAR,
		const Path_& defaultPath = Path_(),
		const int    indent = String :: DEFAULT_LARGE_INDENT
	);
	~ Path();

	const Path_& getPath() const;
	void setPath (const Path_&);

	bool proceedStringOption (const char*, const int, const char* [], int&);
	bool proceedOneCharOption (const char*, const int, const char* [], int&);

	template<class S>
	void showUsageMessage (S&) const;
	template<class S>
	void showOptionValues (S&) const;

	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
};

}
}
}

#endif /*NSTD_CONFIG_OPTION_PATH_HPP_*/
