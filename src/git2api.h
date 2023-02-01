/// \brief Global common libgit2 APIs for rest4git.
/// \author Juniarto Saputra (jsaputra@riseup.net)
/// \version 1.0
/// \date Dec 2022
///
/// Currently there is no detailed description available.
/// \todo Add more detailed description!

#include <string>
#ifdef LIBGIT2_AVAILABLE
#include <cstdint>
#include <sstream>
#include <memory>
#include <git2.h>
#include "singleton.h"

namespace rest4git
{

class Git2API : public Notcopyable
{
public:
  static rest4git::Git2API& get_instance();
public:
  void git_status(std::stringstream& ss);
  void git_branch(std::stringstream& ss, bool all = false);
  void git_lf_files(std::stringstream& ss, const std::string& pattern);
  void git_blame(std::stringstream& ss, const std::string& file, uint32_t from = 1, uint32_t to = 0);
  void git_show(std::stringstream& ss, const std::string& file, uint32_t from = 1, uint32_t to = 0);
  void git_log(std::stringstream& ss, uint32_t max = 0, bool oneline = false, const std::string& file = "");
public:
  const std::string& current_branch_name() const;
protected:
  explicit Git2API();
  virtual ~Git2API();
protected:
  bool okay(std::stringstream &ss) const;
  bool okay() const;
private:
  std::unique_ptr<git_repository, decltype(&git_repository_free)> m_repo;
  std::unique_ptr<git_reference, decltype(&git_reference_free)> m_ref;
  std::string m_current_branch_name;
};

} // rest4git

#endif // LIBGIT2_AVAILABLE