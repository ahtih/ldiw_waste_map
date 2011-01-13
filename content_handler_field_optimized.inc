<?php
// $Id

class content_handler_field_optimized extends content_handler_field_multiple
{
	function init(&$view,$options)
		{
			parent::init($view,$options);
			$this->node_type_to_column=array();

			}

	function theme($values)
		{
			// return theme($this->theme_functions(),$this->view,$this,$values);
			// return $this->render($values);

			$type=$values->{$this->aliases['type']};
			if (!isset($this->node_type_to_column[$type])) {
				$db_info=content_database_info(content_fields(
								$this->content_field['field_name'],$type));
				$this->node_type_to_column[$type]=$this->aliases[
								$db_info['columns']['value']['column']];
				}

			$value=$values->{$this->node_type_to_column[$type]};
			if ($value === NULL)
				$value='';
			return $value;
			}
	}
