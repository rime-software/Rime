<?hh // strict

namespace Rime\ActionView\Render;

class View extends BaseView
{

  public function __invoke($vars = array())
  {
    $this->setTemplateRegistry($this->getViewRegistry());
    $this->setContent($this->render($this->getView(),$vars));

    $layout = $this->getLayout();
    if (! $layout) 
    {
      return $this->getContent();
    }
  
    $this->setTemplateRegistry($this->getLayoutRegistry());
    return $this->render($layout,$vars);
  }
  
  public function render($name, $vars = array())
  {
    ob_start();
    $this->getTemplate($name)->__invoke($vars);
    return ob_get_clean();
  }
}