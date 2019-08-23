#ifndef FD_SYSTEM_HPP
#define FD_SYSTEM_HPP

#include "body_detector.hpp"
#include "notifier.hpp"
#include "fd_state.hpp"
#include "fd_timer.hpp"
#include "retval.hpp"

#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

namespace hcv
{
	class IFDState;
	class IFDBaseState;

	class FDSystem
	{
		//// Methods
		public:
			FDSystem(BodyDetector* const, FDTimer* const, IFDBaseState* const, Notifier* const);

			~FDSystem();

			RetVal Start(const int&);

//			RetVal Stop();

		private:
			friend class IFDState;

//			RetVal changeBaseState(const IFDBaseState*);
//
//			RetVal changeCurrentState(const IFDState*);
//
//			RetVal handleFrameWithBody();
//
//			RetVal handleFrameWithNoBody();

		//// Data
		private:
			BodyDetector* m_p_body_detector;

			FDTimer* m_p_timer;

			IFDBaseState* m_p_base_system_state;

			IFDState* m_p_current_system_state;

			Notifier* m_p_notifier;

	};
} // namespace hcv

#endif // FD_SYSTEM_HPP
