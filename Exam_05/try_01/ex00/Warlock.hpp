#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>

class Warlock
{
	private:
		std::string name;
		std::string title;

		Warlock(void);
		Warlock(const Warlock &src);
		Warlock &operator=(const Warlock &rhs);

	public:
		Warlock(std::string name, std::string title);
		~Warlock(void);

		std::string const &getName(void) const;
		std::string const &getTitle(void) const;
		void setTitle(std::string const &str);

		void introduce() const;
};

#endif
