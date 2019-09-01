#ifndef ASV_SYSTEM_HPP
#define ASV_SYSTEM_HPP

#include "body_detector.hpp"
#include "notifier.hpp"
#include "asv_state.hpp"
#include "asv_timer.hpp"
#include "retval.hpp"

#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

namespace hcv
{
	namespace asv
	{
		class IASVState;
		class IASVBaseState;

		class ASVSystem
		{
			//// Methods
			public:
				ASVSystem(BodyDetector* const, ASVTimer* const, IASVBaseState* const, Notifier* const);

				~ASVSystem();

				RetVal Start(const int&);

	//			RetVal Stop();

			private:
				friend class IASVState;

	//			RetVal changeBaseState(const IASVBaseState*);
	//
	//			RetVal changeCurrentState(const IASVState*);
	//
	//			RetVal handleFrameWithBody();
	//
	//			RetVal handleFrameWithNoBody();

			//// Data
			private:
				BodyDetector* m_p_body_detector;

				ASVTimer* m_p_timer;

				IASVBaseState* m_p_base_system_state;

				IASVState* m_p_current_system_state;

				Notifier* m_p_notifier;

		};

	} // namespace asv
} // namespace hcv

#endif // ASV_SYSTEM_HPP
