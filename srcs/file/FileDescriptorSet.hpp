#ifndef FILEDESCRIPTORSET_HPP
# define FILEDESCRIPTORSET_HPP

#include <sys/select.h>

class FileDescriptorSet
{
	private:
		fd_set m_storage;
		int m_size;

	public:
		static const int MAX;

	public:
		FileDescriptorSet();
		FileDescriptorSet(const FileDescriptorSet &other);

		virtual
		~FileDescriptorSet();

		FileDescriptorSet&
		operator=(const FileDescriptorSet &other);

		void
		zero();

		void
		set(int n);

		void
		clear(int n);

		bool
		test(int n) const;

		int
		size() const;

		bool
		empty() const;

		fd_set&
		storage();
};

#endif
