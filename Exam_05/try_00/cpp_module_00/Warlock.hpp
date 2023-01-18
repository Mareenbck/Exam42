#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>

class Warlock
{
	private:
		std::string name;
		std::string title;

		Warlock(void);
		Warlock(Warlock const &src);
		Warlock &operator=(Warlock const &rhs);

	public:
		Warlock(std::string name, std::string title);
		~Warlock(void);

		std::string const &getName(void) const;
		std::string const &getTitle(void) const;
		void setTitle(std::string const &str);

		void introduce() const;
};

#endif
