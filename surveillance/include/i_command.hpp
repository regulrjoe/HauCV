#ifndef COMMANDS_HPP
#define COMMANDS_HPP

namespace hcv
{

	////////////////////// ICommand
	class ICommand
	{
		public:
			virtual ~ICommand() {};
			virtual void Execute() = 0;

		protected:
			ICommand() {}
	};

} // namespace hcv

#endif // I_COMMAND_HPP
