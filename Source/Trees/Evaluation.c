/**/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <float.h>

#include "Common/Common.h"
#include "Error/Error.h"

/**/
float Evaluate_Operator(float _operator, float _operand_left, float _operand_right)
{
	auto float _return_val = 0;

	/* Binary operators */
		/* Multiplication */
	if		(MULTIPLY	== _operator)
	{
		/* Ineffective member detection, 1 for multiplication */
		_operand_left	= ((BLANK == _operand_left)  ? ((float)1.0) : (_operand_left));
		_operand_right	= ((BLANK == _operand_right) ? ((float)1.0) : (_operand_right));

		_return_val		= _operand_left * _operand_right;
	}
		/* Division */
	else if (DIVIDE		== _operator)
	{
		/* Division by 0 protection */
			/* Ignore the division and continue operation, based on the error toleration the evaluation can be terminated */
		if (!_operand_right)
		{
			/* Inform the user on the intermediate operation */
#ifdef _DEBUG_
			printf("\n\tWarning:\n\t\tDenominator is detected to be 0!\n\t\tPlease correct the input tree.\n\t\tOtherwise an intermediate calculation is resulted in 0.");
#endif // _DEBUG_

			return _operand_left;
		}
		/* Ineffective member detection, return the non-blank value */
		else if ((BLANK == _operand_left) || (BLANK == _operand_right))
		{
			_return_val = ((BLANK == _operand_left) ? (_operand_right) : (_operand_left));
		}
		else
		{
			_return_val = _operand_left / _operand_right;
		}
	}
		/* Addition */
	else if (ADD		== _operator)
	{
		/* Ineffective member detection, 0 for addition */
		_operand_left	= ((BLANK == _operand_left)  ? ((float)0) : (_operand_left));
		_operand_right	= ((BLANK == _operand_right) ? ((float)0) : (_operand_right));

		_return_val		= _operand_left + _operand_right;
	}
		/* Subtraction */
	else if (SUB		== _operator)
	{
		/* Ineffective member detection, return the non-blank value */
		if ((BLANK		== _operand_left) || (BLANK == _operand_right))
		{
			_return_val = ((BLANK == _operand_left) ? (_operand_right) : (_operand_left));
		}
		else
		{
			_return_val = _operand_left - _operand_right;
		}
	}
	/* Unary operators */
		/* Cube */
	else if (CUBE		== _operator)
	{
		auto float _temp;

		/* Sanity check */
		if ((BLANK != _operand_left) && (BLANK != _operand_right))
		{
#ifdef _DEBUG_
			printf("\n\tWarning:\n\t\tMore than 1 node is detected under a unary operator [CUBE]!\n\t\tRight node is ignored during the evaluation."		\
					"\n\t\tPlease correct the input tree.");
#endif // _DEBUG_

			/* Return the left operand after evaluation, ignore the right operand */
			_return_val = _operand_left * _operand_left * _operand_left;
		}
		/* Find the non-blank node first */
		else
		{
			_temp		= ((BLANK == _operand_left) ? (_operand_right) : (_operand_left));
			_return_val = _temp * _temp * _temp;
		}
	}
		/* Square */
	else if (SQUARE		== _operator)
	{
		auto float _temp;

		/* Sanity check */
		if ((BLANK != _operand_left) && (BLANK != _operand_right))
		{
#ifdef _DEBUG_
			printf("\n\tWarning:\n\t\tMore than 1 node is detected under a unary operator [SQUARE]!\n\t\tRight node is ignored during the evaluation."	\
				"\n\t\tPlease correct the input tree.");
#endif // _DEBUG_

			/* Return the left operand after evaluation, ignore the right operand */
			_return_val = _operand_left * _operand_left;
		}
		/* Find the non-blank node first */
		else
		{
			_temp		= ((BLANK == _operand_left) ? (_operand_right) : (_operand_left));
			_return_val = _temp * _temp;
		}
	}
		/* No operator provided */
	else
	{
		/* Return a blank value */
		return BLANK;
	}

	return _return_val;
}