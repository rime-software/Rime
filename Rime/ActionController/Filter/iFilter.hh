<?hh // strict

namespace Rime\ActionController\Filter;

interface iFilter
{
  public function filter(string $action, array $filters): array;
}