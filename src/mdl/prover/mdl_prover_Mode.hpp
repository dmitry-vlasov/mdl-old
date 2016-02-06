/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_prover_Mode.hpp                                      */
/* Description:     class for the prover show mode                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {

class Mode : public mdl :: Mode {
public :
	enum {
		END_LINE = expression :: Mode :: MAX_BIT + 1,
		SHOW_TREE_STATISTICS, //< show only statistical info
		SHOW_UP_TREE_CARD,
		SHOW_UP_TREE_VOLUME,
		SHOW_UP_TREE_LEVELS,
		SHOW_UP_TREE_LEVELS_CARD,
		SHOW_UP_TREE_EXP_VOLUME,
		SHOW_UP_TREE_FITNESS,
		SHOW_UP_TREE_PARTITION,
		SHOW_UP_CROWN_CARD,
		SHOW_UP_CROWN_VOLUME,
		SHOW_UP_CROWN_H_MIN,
		SHOW_UP_CROWN_H_MAX,

		SHOW_DOWN_TREE_CARD,
		SHOW_DOWN_TREE_VOLUME,
		SHOW_DOWN_CROWN_CARD,
		SHOW_DOWN_CROWN_VOLUME,
		SHOW_DOWN_ROOT_CARD,

		SHOW_USED_VOLUME,
		SHOW_BALANCE,
		SHOW_TREE_VOLUME,
		SHOW_GROW_UP_VELOCITY,
		SHOW_GROW_DOWN_VELOCITY,
		SHOW_EXPRESSION_VOLUME,

		SHOW_IN_GML, //< show in gml graph presentation format
		SHOW_IN_GML_GRAPH,
		SHOW_IN_GML_NODE,
		SHOW_IN_GML_EVIDENCE,

		SHOW_IN_GML_EXPRESSION,
		SHOW_IN_GML_ASSERTION,
		SHOW_IN_GML_WEIGHT,
		SHOW_IN_GML_ADDRESS,
		SHOW_IN_GML_HEIGHT_MIN,
		SHOW_IN_GML_HEIGHT_MAX,
		SHOW_IN_GML_SUBSTITUTION,
		SHOW_IN_GML_DEPTH,

		SHOW_ONLY_HINT,
		SHOW_HINT_STAT,

		SHOW_FULL_DESCRIPTION,

		MAX_BIT = SHOW_FULL_DESCRIPTION
	};

	Mode ();
	Mode (const String&);
	Mode (const Mode&);
};

}
}


