#ifndef I_COMMAND_HPP
#define I_COMMAND_HPP

namespace hcv
{

	////////////////////// ICommand
	class ICommand
	{
		public:
			virtual ~ICommand() = 0;
			void Execute();

		protected:
			ICommand();
	};

} // namespace hcv

#endif // I_COMMAND_HPP
